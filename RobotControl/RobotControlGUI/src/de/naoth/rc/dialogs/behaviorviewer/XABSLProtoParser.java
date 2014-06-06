/*
 * 
 */
package de.naoth.rc.dialogs.behaviorviewer;

import de.naoth.rc.messages.Messages;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

/**
 *
 * @author Heinrich Mellmann
 */
public class XABSLProtoParser {

    private XABSLBehavior behavior = null;

    public XABSLBehaviorFrame parse(Messages.BehaviorStateSparse status) {
        XABSLBehaviorFrame frame = new XABSLBehaviorFrame(status.getFrameNumber());

        ArrayList<XABSLBehavior.Symbol> inputSymbols = parseSparse(
                behavior.inputSymbols,
                status.getInputSymbolList());
        for (XABSLBehavior.Symbol s : inputSymbols) {
            frame.addInputSymbol(s);
        }

        ArrayList<XABSLBehavior.Symbol> outputSymbols = parseSparse(
                behavior.outputSymbols,
                status.getOutputSymbolList());
        for (XABSLBehavior.Symbol s : outputSymbols) {
            frame.addOutputSymbol(s);
        }

        for (Messages.XABSLActionSparse a : status.getActiveRootActionsList()) {
            frame.actions.add(parse(a));
        }

        return frame;
    }

    public ArrayList<XABSLBehavior.Symbol> parseSparse(
            Map<Integer, XABSLBehavior.Symbol> existing,
            Messages.SymbolValueList valueList) {
        
        ArrayList<XABSLBehavior.Symbol> result
                = new ArrayList<>(valueList.getBooleanCount()
                        + valueList.getDecimalCount()
                        + valueList.getEnumeratedCount());
        
        Set<Integer> includedIDs = new HashSet<>();

        for (Messages.SymbolValueList.DoubleSymbol symbol : valueList.getDecimalList()) {
            XABSLBehavior.Symbol s = existing.get(symbol.getId());
            result.add(parse(s, symbol));
            includedIDs.add(symbol.getId());
        }

        for (Messages.SymbolValueList.BooleanSymbol symbol : valueList.getBooleanList()) {
            XABSLBehavior.Symbol s = existing.get(symbol.getId());
            result.add(parse(s, symbol));
            includedIDs.add(symbol.getId());
        }

        for (Messages.SymbolValueList.EnumSymbol symbol : valueList.getEnumeratedList()) {
            XABSLBehavior.Symbol s = existing.get(symbol.getId());
            result.add(parse((XABSLBehavior.Symbol.Enum) s, symbol));
            includedIDs.add(symbol.getId());
        }
        
        // also add all symbols that are in the existing list but have not been
        // included in the sparse message
        for(Map.Entry<Integer, XABSLBehavior.Symbol> entry : existing.entrySet())
        {
            if(!includedIDs.contains(entry.getKey()))
            {
                result.add(entry.getValue());
            }
        }
        
        return result;
    }

    public XABSLAction parse(Messages.XABSLActionSparse action_msg) {
        if (action_msg.getType() == Messages.XABSLActionSparse.ActionType.Option) {
            Messages.XABSLActiveOptionSparse option_msg = action_msg.getOption();
            XABSLAction.OptionExecution a = new XABSLAction.OptionExecution();

            a.activeState = option_msg.getActiveState();
            a.timeOfExecution = option_msg.getTimeOfExecution();
            a.stateTime = option_msg.getStateTime();
            a.id = option_msg.getId();

            XABSLBehavior.Option protoOption = this.behavior.options.get(a.id);
            a.option = new XABSLBehavior.Option(protoOption); // make a shallow copy

            // TODO: parameters
            for (Messages.XABSLActionSparse sa : option_msg.getActiveSubActionsList()) {
                a.activeSubActions.add(parse(sa));
            }

            return a;
        } else if (action_msg.getType() == Messages.XABSLActionSparse.ActionType.SymbolAssignement) {
            XABSLAction.SymbolAssignement a = new XABSLAction.SymbolAssignement();
            a.symbol = parse(behavior.outputSymbols.get(action_msg.getSymbol().getId()), action_msg.getSymbol());
            return a;
        } else if (action_msg.getType() == Messages.XABSLActionSparse.ActionType.BasicBehavior) {
            XABSLAction.BasicBehaviorExecution a = new XABSLAction.BasicBehaviorExecution();
            a.name = "Some Basic Behavior (not supported yet)";
            return a;
        }

        return null;
    }

    public XABSLBehavior parse(Messages.BehaviorStateComplete behavior_msg) {
        this.behavior = new XABSLBehavior();

        // parse the enumerations first, so they are available when symbols are parsed
        for (int i = 0; i < behavior_msg.getEnumerationsCount(); i++) {
            behavior.enumerations.add(i, parse(behavior_msg.getEnumerations(i)));
        }
        for (int i = 0; i < behavior_msg.getOptionsCount(); i++) {
            behavior.options.add(i, parse(behavior_msg.getOptions(i)));
        }
        for (int i = 0; i < behavior_msg.getAgentsCount(); i++) {
            behavior.agents.add(i, parse(behavior_msg.getAgents(i)));
        }

        behavior.inputSymbols.putAll(parse(behavior_msg.getInputSymbolList()));
        behavior.outputSymbols.putAll(parse(behavior_msg.getOutputSymbolList()));

        return this.behavior;
    }

    public TreeMap<Integer, XABSLBehavior.Symbol> parse(
            Messages.SymbolValueList valueList) {
        TreeMap<Integer, XABSLBehavior.Symbol> result = new TreeMap<>();

        for (Messages.SymbolValueList.DoubleSymbol s_msg : valueList.getDecimalList()) {
            result.put(s_msg.getId(),
                    new XABSLBehavior.Symbol.Decimal(s_msg.getName(), s_msg.getValue()));
        }

        for (Messages.SymbolValueList.BooleanSymbol s_msg : valueList.getBooleanList()) {
            result.put(s_msg.getId(),
                    new XABSLBehavior.Symbol.Boolean(s_msg.getName(),
                            s_msg.getValue()));
        }

        for (Messages.SymbolValueList.EnumSymbol s_msg : valueList.getEnumeratedList()) {
            XABSLBehavior.EnumType enumType = this.behavior.enumerations.get(s_msg.getTypeId());
            result.put(s_msg.getId(),
                    new XABSLBehavior.Symbol.Enum(s_msg.getName(), enumType, s_msg.getValue()));
        }

        return result;
    }

    private XABSLBehavior.Option parse(Messages.BehaviorStateComplete.Option option_msg) {
        XABSLBehavior.Option option = new XABSLBehavior.Option(option_msg.getName());

        for (int j = 0; j < option_msg.getParametersCount(); j++) {
            option.parameters.add(j, parse(option_msg.getParameters(j)));
        }

        for (int j = 0; j < option_msg.getStatesCount(); j++) {
            option.states.add(j, parse(option_msg.getStates(j)));
        }

        return option;
    }

    private XABSLBehavior.Option.State parse(Messages.BehaviorStateComplete.Option.State state_msg) {
        return new XABSLBehavior.Option.State(state_msg.getName(), state_msg.getTarget());
    }

    private XABSLBehavior.Symbol parse(Messages.XABSLSymbol p_msg) 
    {
        XABSLBehavior.Symbol p = new XABSLBehavior.Symbol(p_msg.getName());
        return parse(p, p_msg);
    }

    private XABSLBehavior.Symbol parse(XABSLBehavior.Symbol p, Messages.XABSLSymbol p_msg) {
        switch (p_msg.getType()) {
            case Decimal:
                return p.createDecimal(p_msg.getDecimalValue());
            case Boolean:
                return p.createBoolean(p_msg.getBoolValue());
            case Enum:
                XABSLBehavior.EnumType enumeration = this.behavior.enumerations.get(p_msg.getEnumTypeId());
                return p.createEnum(enumeration, p_msg.getEnumValue());
        }
        return p;
    }

    private XABSLBehavior.Symbol parse(XABSLBehavior.Symbol s, Messages.SymbolValueList.DoubleSymbol s_msg) {
        return s.createDecimal(s_msg.getValue());
    }

    private XABSLBehavior.Symbol parse(XABSLBehavior.Symbol s, Messages.SymbolValueList.BooleanSymbol s_msg) {
        return s.createBoolean(s_msg.getValue());
    }

    private XABSLBehavior.Symbol parse(XABSLBehavior.Symbol.Enum s, Messages.SymbolValueList.EnumSymbol s_msg) {
        return s.createEnum(s.enumType, s_msg.getValue());
    }

    private XABSLBehavior.Agent parse(Messages.BehaviorStateComplete.Agent agent_msg) {
        XABSLBehavior.Agent agent = new XABSLBehavior.Agent();
        agent.name = agent_msg.getName();
        agent.rootOption = agent_msg.getRootOption();
        return agent;
    }

    private XABSLBehavior.EnumType parse(Messages.BehaviorStateComplete.EnumType enum_msg) {
        XABSLBehavior.EnumType enumeration = new XABSLBehavior.EnumType();
        enumeration.name = enum_msg.getName();
        for (Messages.BehaviorStateComplete.EnumType.Element msgElement : enum_msg.getElementsList()) {
            XABSLBehavior.EnumType.Element e = parse(msgElement);
            enumeration.elements.put(e.value, e);
        }
        return enumeration;
    }

    private XABSLBehavior.EnumType.Element parse(Messages.BehaviorStateComplete.EnumType.Element element_msg) {
        XABSLBehavior.EnumType.Element element = new XABSLBehavior.EnumType.Element();
        element.name = element_msg.getName();
        element.value = (int) element_msg.getValue();
        return element;
    }
}
