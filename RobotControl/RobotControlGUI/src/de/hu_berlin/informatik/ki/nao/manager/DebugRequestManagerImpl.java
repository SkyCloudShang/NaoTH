/*
 * 
 */
package de.hu_berlin.informatik.ki.nao.manager;

import de.hu_berlin.informatik.ki.nao.server.Command;
import net.xeoh.plugins.base.annotations.PluginImplementation;

/**
 *
 * @author Heinrich Mellmann
 */
@PluginImplementation
public class DebugRequestManagerImpl extends AbstractManagerPlugin<String[]>
  implements DebugRequestManager
{

  @Override
  public String[] convertByteArrayToType(byte[] result) throws IllegalArgumentException
  {
    String[] messages = (new String(result)).split("\n");
    return messages;
  }

  @Override
  public Command getCurrentCommand()
  {
    return new Command("debug_request:list");
  }
}//end class DebugRequestManager

