from __future__ import division
import os
from matplotlib import pyplot as plt
import numpy as np
import pickle

"""
Evaluates the data generated by ../simulate_every_pos.py

Example:
    run without any parameters

        $ python evaluate_every_pos.py
"""


def check_equality(lst):
    return not lst or [lst[0]] * len(lst) == lst


# Dummy List for appending all pickle files
dumped_decisions = ([])
sample_list = ([])


def load_bachelor_decisions():
    # the data con be downloaded from https://www2.informatik.hu-berlin.de/~schlottb/ressources/ActionSelectionBA_data.zip
    # define prefix for data
    data_prefix = "D:/RoboCup/Paper-Repos/Bachelor-Schlotter/data/"

    sample_list.extend([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300])
    sample_list.extend([400, 500, 600, 700, 800, 900, 1000])

    for i in sample_list:
        filename = '{}{:d}{}'.format(str(data_prefix) + "simulate_every_pos-", i, "-100.pickle")
        dumped_decisions.append(pickle.load(open(filename, "rb")))


def load_humanoids_decision():
    # the data con be downloaded from https://www2.informatik.hu-berlin.de/~schlottb/ressources/ActionSelection_data.zip
    # define prefix for data
    data_prefix = "D:/RoboCup/Paper-Repos/2017-humanoids-action-selection/data/"

    sample_list.extend([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 30, 40, 50, 60, 70])
    for i in sample_list:
        filename = '{}{:d}{}'.format(str(data_prefix) + "simulate_every_pos-", i, "-100-v0.pickle")
        dumped_decisions.append(pickle.load(open(filename, "rb")))


def check_data_consistency():
    # check if the number of states is the same for all experiments
    counts = []
    for decisions in dumped_decisions:
        counts.append(len(decisions))

    print("Number of states in each experiment: ")
    print(counts)
    if not check_equality(counts):
        print("the numbers are not equal - the following analysis can not be valid")


def calculate_uncertainties():
    # Calculate the uncertainty of the decisions
    file_idx = 0

    # check if file already exists
    while os.path.exists("../data/total_uncertainties_" + str(file_idx) + ".txt"):
        file_idx += 1

    # TODO change name according to percentage
    with open("../data/total_uncertainties_" + str(file_idx) + ".txt", "w") as f:
        print("Number of states with too uncertain decisions / total number of states")
        for count, decisions in enumerate(dumped_decisions):
            confidence_vector = []

            for pos_dump in decisions:
                new_x, new_y, new_rot, new_decision_histogram = pos_dump

                # calculate how many times out of 100 the same best decision was chosen
                confidence_vector.append(max(new_decision_histogram) / 100)

            # filter the states where the decision was too uncertain
            x = [i for i in confidence_vector if i <= 0.5]
            print(len(x) / len(confidence_vector))  # len(confidence_vector) = number of states
            f.write(str(sample_list[count]) + "\t" + str(len(x) / len(confidence_vector)) + "\n")


def plot_uncertainties():  # Plot the uncertainties in a scalar plot
    fixed_rotation = 0
    # load single decision file
    data_prefix = "D:/RoboCup/Paper-Repos/2017-humanoids-action-selection/data/"
    decisions = pickle.load(open(str(data_prefix) + "simulate_every_pos-30-100-v0.pickle", "rb"))

    #
    nx = {}
    ny = {}
    for pos in decisions:
        x, y, rotation, new_decision_histogram = pos
        if rotation == fixed_rotation:
            nx[x] = x
            ny[y] = y

    nxi = np.array(sorted(nx.keys()))
    nyi = np.array(sorted(ny.keys()))

    for i, v in enumerate(nxi):
        nx[v] = i

    for i, v in enumerate(nyi):
        ny[v] = i

    f = np.zeros((len(ny), len(nx)))

    #
    for pos in decisions:
        x, y, rotation, new_decision_histogram = pos
        if rotation == fixed_rotation:
            f[ny[y], nx[x]] = max(new_decision_histogram) / 100

    #
    plt.pcolor(nxi, nyi, f)
    plt.colorbar()
    plt.show()


if __name__ == "__main__":
    # load_bachelor_decisions()
    # load_humanoids_decision()

    # check_data_consistency()
    # calculate_uncertainties()
    plot_uncertainties()
