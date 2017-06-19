from __future__ import division
import sys
import math
import numpy as np
from matplotlib import pyplot as plt
from matplotlib.patches import Circle
import matplotlib as mpl
import Queue as Q
import copy
import field_info as f

robot_radius = 300

def stupid_experiment(start, target, obstacles):
    return hit_obstacle(start, target, obstacles) is None

def draw_field(ax, x_off, y_off):
    ax.plot([0 +x_off, 0+x_off], [-f.y_length * 0.5 + y_off, f.y_length * 0.5 + y_off], 'white')  # Middle line

    ax.plot([f.x_opponent_groundline+x_off, f.x_opponent_groundline+x_off], [f.y_left_sideline+y_off, f.y_right_sideline+y_off], 'white')  # opponent ground line
    ax.plot([f.x_own_groundline+x_off, f.x_own_groundline+x_off], [f.y_right_sideline+y_off, f.y_left_sideline+y_off], 'white')  # own ground line

    ax.plot([f.x_own_groundline+x_off, f.x_opponent_groundline+x_off], [f.y_left_sideline+y_off, f.y_left_sideline+y_off], 'white')
    ax.plot([f.x_own_groundline+x_off, f.x_opponent_groundline+x_off], [f.y_right_sideline+y_off, f.y_right_sideline+y_off], 'white')

    ax.plot([f.x_opponent_groundline-f.x_penalty_area_length+x_off, f.x_opponent_groundline-f.x_penalty_area_length+x_off], [-f.y_penalty_area_length*0.5+y_off, f.y_penalty_area_length*0.5+y_off], 'white')  # opp penalty
    ax.plot([f.x_opponent_groundline+x_off, f.x_opponent_groundline-f.x_penalty_area_length+x_off], [f.y_penalty_area_length*0.5+y_off, f.y_penalty_area_length*0.5+y_off], 'white')  # opp penalty
    ax.plot([f.x_opponent_groundline+x_off, f.x_opponent_groundline-f.x_penalty_area_length+x_off], [-f.y_penalty_area_length*0.5+y_off, -f.y_penalty_area_length*0.5+y_off], 'white')  # opp penalty

    ax.plot([f.x_own_groundline+f.x_penalty_area_length+x_off, f.x_own_groundline+f.x_penalty_area_length+x_off], [-f.y_penalty_area_length*0.5+y_off, f.y_penalty_area_length*0.5+y_off], 'white')  # own penalty
    ax.plot([f.x_own_groundline+x_off, f.x_own_groundline+f.x_penalty_area_length+x_off], [f.y_penalty_area_length*0.5+y_off, f.y_penalty_area_length*0.5+y_off], 'white')  # own penalty
    ax.plot([f.x_own_groundline+x_off, f.x_own_groundline+f.x_penalty_area_length+x_off], [-f.y_penalty_area_length*0.5+y_off, -f.y_penalty_area_length*0.5+y_off], 'white')  # own penalty

    # Middle Circle
    ax.add_artist(Circle(xy=(0+x_off, 0+y_off), radius=f.center_circle_radius, fill=False, edgecolor='white'))
    # Penalty Marks
    ax.add_artist(Circle(xy=(f.x_opponent_groundline - f.x_penalty_mark_distance+x_off, 0+y_off), radius=f.penalty_cross_radius, color='white'))
    ax.add_artist(Circle(xy=(f.x_own_groundline + f.x_penalty_mark_distance+x_off, 0+y_off), radius=f.penalty_cross_radius, color='white'))

    # Own goal box
    ax.add_artist(Circle(xy=(f.own_goalpost_right.x+x_off, f.own_goalpost_right.y+y_off), radius=f.goalpost_radius, color='white'))  # GoalPostRight
    ax.add_artist(Circle(xy=(f.own_goalpost_left.x+x_off, f.own_goalpost_left.y+y_off), radius=f.goalpost_radius, color='white'))  # GoalPostLeft
    ax.plot([f.x_own_groundline+x_off, f.x_own_groundline - f.goal_depth+x_off], [-f.goal_width*0.5+y_off, -f.goal_width*0.5+y_off], 'white')  # own goal box
    ax.plot([f.x_own_groundline+x_off, f.x_own_groundline - f.goal_depth+x_off], [f.goal_width*0.5+y_off, f.goal_width*0.5+y_off], 'white')  # own goal box
    ax.plot([f.x_own_groundline - f.goal_depth+x_off, f.x_own_groundline - f.goal_depth+x_off], [-f.goal_width*0.5+y_off, f.goal_width*0.5+y_off], 'white')  # own goal box

    # Opp GoalBox
    ax.add_artist(Circle(xy=(f.opponent_goalpost_right.x+x_off, f.opponent_goalpost_right.y+y_off), radius=f.goalpost_radius, color='white'))  # GoalPostRight
    ax.add_artist(Circle(xy=(f.opponent_goalpost_left.x+x_off, f.opponent_goalpost_left.y+y_off), radius=f.goalpost_radius, color='white'))  # GoalPostLeft
    ax.plot([f.x_opponent_groundline+x_off, f.x_opponent_groundline + f.goal_depth+x_off], [-f.goal_width*0.5+y_off, -f.goal_width*0.5+y_off], 'white')  # Opp goal box
    ax.plot([f.x_opponent_groundline+x_off, f.x_opponent_groundline + f.goal_depth+x_off], [f.goal_width*0.5+y_off, f.goal_width*0.5+y_off], 'white')  # Opp goal box
    ax.plot([f.x_opponent_groundline + f.goal_depth+x_off, f.x_opponent_groundline + f.goal_depth+x_off], [-f.goal_width*0.5+y_off, f.goal_width*0.5+y_off], 'white')  # Opp goal box

    ax.set_axis_bgcolor('green')

def draw_obstacles(ax, obstacles):
    # draw obstacles
    if obstacles:
        for k in obstacles:
            ax.add_artist(Circle(xy=(k[0], k[1]), radius=k[2], fill=True, color='black', alpha=.25))
            ax.add_artist(Circle(xy=(k[0], k[1]), radius=10, fill=True, color='black'))

def draw_robot(ax, robot_pos):
    ax.add_artist(Circle(xy=(robot_pos[0], robot_pos[1]), radius=robot_radius, fill=True, color='black', alpha=.5))

def draw_target(ax, target):
    ax.plot(target[0], target[1], 'x', color='red')

def draw_steps(ax, robot_pos, trajectory, col):
    x_dist = robot_pos[0]
    y_dist = robot_pos[1]
    path   = []
    for k in trajectory:
        path.append((k[0] + x_dist, k[1] + y_dist))
        x_dist += k[0]
        y_dist += k[1]
    for k in range(0, len(path) - 1):
        ax.plot([path[k][0], path[k+1][0]], [path[k][1], path[k+1][1]], c=col)

def dist(start, target):
    return np.sqrt(np.power(start[0] - target[0], 2) + np.power(start[1] - target[1], 2))

def hit_obstacle(start, target, obstacles):
    hits = []
    for obst in obstacles:
        start_to_obst = (obst[0] - start[0], obst[1] - start[1])
        line  = (target[0] - start[0], target[1] - start[1])

        line_mag = np.power(line[0], 2) + np.power(line[1], 2)
        start_dot_obst = start_to_obst[0] * line[0] + start_to_obst[1] * line[1]

        t = start_dot_obst / line_mag

        if (t < 0):
            point = start
            continue
        elif (t > 1):
            point = target
            continue
        else:
            point = (start[0] + line[0] * t, start[1] + line[1] * t)

        if dist(point, obst) <= obst[2] + robot_radius - 50:
            hits.append((obst, t))

    if len(hits) > 0:
        minim = hits[0]
        for k in range(1, len(hits)):
            if hits[k][1] < minim[1]:
                    minim = hits[k]
        return minim[0]

    return None

def has_collided(vec, obstacles):
    for k in obstacles:
        if dist(vec, k) <= k[2] + robot_radius:
            return True
    return False\

def length_of_trajectory(t):
    length = 0
    if len(t) == 0 :
        return 0

    # hack
    tnp = np.array(t)
    for k in range(1, len(t)):
        length +=  np.linalg.norm(tnp[k, :] - tnp[k-1, :])
    return length

def compute_sub_target_it(start, target, obstacles, ax, sign):
    collision = hit_obstacle(start, target, obstacles)
    if collision is None:
        return None

    offset = 1

    target_vec  = (target[0] - start[0], target[1] - start[1])
    target_dist = np.linalg.norm(np.array(target_vec))
    unit_vec    = (target_vec[0] / target_dist, target_vec[1] / target_dist)

    orth_vec1 = (unit_vec[1] * -1, unit_vec[0])
    orth_vec2 = (unit_vec[1], unit_vec[0] * -1)

    if sign == 1:
        sub_target = (orth_vec1[0] * robot_radius + collision[0], orth_vec1[1] * robot_radius + collision[1])
    else:
        sub_target = (orth_vec2[0] * robot_radius + collision[0], orth_vec2[1] * robot_radius + collision[1])

    while has_collided(sub_target, obstacles):
        offset += robot_radius
        if sign == 1:
            sub_target = (orth_vec1[0] * (robot_radius + offset) + collision[0], orth_vec1[1] * (robot_radius + offset) + collision[1])
        else:
            sub_target = (orth_vec2[0] * (robot_radius + offset) + collision[0], orth_vec2[1] * (robot_radius + offset) + collision[1])

    return sub_target

def compute_path_it(start, target, obstacles, depth, ax, sign, show_sub):
    trajectory = [(start, target)]
    waypoints = [start, target]

    while True:
        if depth > 10:
            return trajectory
        depth += 1
        counter = 0
        tmp_waypoints = copy.copy(waypoints)
        for k in range(0, len(waypoints) - 1):
            sub_target1 = compute_sub_target_it(waypoints[k], waypoints[k+1], obstacles, ax, +1)
            sub_target2 = compute_sub_target_it(waypoints[k], waypoints[k+1], obstacles, ax, -1)

            if sub_target1 is not None and sub_target2 is not None:
                tmp_waypoints1 = copy.copy(waypoints)
                tmp_waypoints2 = copy.copy(waypoints)
                tmp_waypoints1.insert(k+1, sub_target1)
                tmp_waypoints2.insert(k+1, sub_target2)
                dist1 = 0
                dist2 = 0
                for l in range(0, len(tmp_waypoints1) - 1):
                    dist1 += length_of_trajectory((tmp_waypoints1[l], tmp_waypoints1[l+1]))
                    dist2 += length_of_trajectory((tmp_waypoints2[l], tmp_waypoints2[l+1]))
                #if len(tmp_waypoints1) < len(tmp_waypoints2) and np.absolute(dist1) - np.absolute(dist2) < 1000:
                if dist1 < dist2:
                    sub_target = sub_target1
                else:
                    sub_target = sub_target2

                counter += 1
                tmp_waypoints.insert(k+1, sub_target)
            else:
                continue

            if show_sub > 0 and sub_target is not None:
                #ax.plot(sub_target1[0], sub_target1[1], 'x', c='blue')
                #ax.plot(sub_target2[0], sub_target2[1], 'x', c='white')
                ax.plot(sub_target[0], sub_target[1], 'x', c='white')


        waypoints = copy.copy(tmp_waypoints)
        trajectory = []
        for k in range(0, len(waypoints) - 1):
            trajectory.append((waypoints[k], waypoints[k+1]))
        if counter == 0:
            return trajectory

def get_gait(robot_pos, target, obstacles, depth, ax, show_sub):
    trajectory  = compute_path_it(robot_pos, target, obstacles, 0, ax, None, show_sub)
    ax.plot(trajectory[0][1][0], trajectory[0][1][1], 'x', c='red')

    direction = np.array(trajectory[0][1]) - np.array(trajectory[0][0])
    distance  = np.linalg.norm(direction)

    if distance > 0:
        gait_unit_vec  = direction / distance
        max_steplength = min(60, max(-60, distance))
        gait           = (gait_unit_vec[0] * max_steplength, gait_unit_vec[1] * max_steplength)
    else:
        gait = (0,0)

    return gait, trajectory
