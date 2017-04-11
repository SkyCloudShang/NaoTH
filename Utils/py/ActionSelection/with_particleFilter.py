import math
import numpy as np
from matplotlib import pyplot as plt
from matplotlib.patches import Circle
from tools import action as a
from tools import Simulation as Sim
from naoth import math2d as m2d
from tools import tools


class State:
    def __init__(self):
        self.pose = m2d.Pose2D()
        self.pose.translation = m2d.Vector2(4200, 0)
        self.pose.rotation = math.radians(0)

        self.ball_position = m2d.Vector2(100.0, 0.0)

        self.obstacle_list = ([])  # is in global coordinates


def draw_actions(actions_consequences, state, best_action):
    plt.clf()
    tools.draw_field()

    axes = plt.gca()
    axes.add_artist(Circle(xy=(state.pose.translation.x, state.pose.translation.y), radius=100, fill=False, edgecolor='white'))
    axes.text(0, 0, best_action, fontsize=12)

    x = np.array([])
    y = np.array([])

    for consequence in actions_consequences:
        for particle in consequence.positions():
            ball_pos = state.pose * particle.ball_pos  # transform in global coordinates

            x = np.append(x, [ball_pos.x])
            y = np.append(y, [ball_pos.y])

    plt.scatter(x, y, c='r', alpha=0.5)
    plt.pause(0.0001)


def main():
    state = State()

    no_action = a.Action("none", 0, 0, 0, 0)
    kick_short = a.Action("kick_short", 780, 150, 8.454482265522328, 6.992268841997358)
    sidekick_left = a.Action("sidekick_left", 750, 150, 86.170795364136380, 10.669170653645670)
    sidekick_right = a.Action("sidekick_right", 750, 150, -89.657943335302260, 10.553726275058064)

    action_list = [no_action, kick_short, sidekick_left, sidekick_right]
    # Todo Implement the particle filter here somehow
    # Todo change the directions of the best action/ or all actions
    # Sample is element of [0, 360)
    # Sample is evaluated by simulating the consequences and calculating the best actions
    # TODO: Problem: decide function gives only the best action and not a sorted list of actions
    # as far as I understand it we need that in order to resample the worst n samples and eventually converge
    # i dont know what the best way to do that is

    # For Particle Filter:
    a.num_particles = 1
    # TODO: Create n random numbers here:
    while True:
        actions_consequences = []
        # Simulate Consequences

        single_consequence = a.ActionResults([])
        actions_consequences.append(Sim.simulate_consequences(kick_short, single_consequence, state))

        # actions_consequences is now a list of ActionResults

        # Decide best action
        best_action = Sim.decide_smart(actions_consequences, state)

        draw_actions(actions_consequences, state, action_list[best_action].name)



if __name__ == "__main__":
    main()
