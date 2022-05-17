# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")
    teams = []

    # TODO: Read teams into memory from file

    # Opening the CSV Teams file
    file = open(sys.argv[1], 'r')

    # Saving all the listed teams in a list of dictionaries
    file_input = csv.DictReader(file)
    for row in file_input:
        teams.append(row)

    # Converting the Ratings from string to integer type
    for team in teams:
        team['rating'] = int(team['rating'])

    # Filling a dictionary with the World Cup teams
    counts = filling_dict()

    # Calculating the winner
    for i in range(N):
        champion = simulate_tournament(teams)
        filling_winners(counts, champion)
    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")

    file.close()


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    while len(teams) > 1:
        teams = simulate_round(teams)
    # The winner currently is a dictionary, accessing the value using the team key
    champ = teams[0]['team']
    return champ


# Function responsible for increasing the winning count of a given team
def filling_winners(counts, champ):
    for team in counts:
        if champ in team:
            counts[champ] += 1


# Function that creates a dictionary with all the teams of the World Cup
def filling_dict():
    teams = []
    counts = {}
    # Opening the corresponding file
    file = open(sys.argv[1], "r")
    lines = file.readlines()
    # Reading line by line
    for line in lines:
        temp_line = line.rstrip('\n')
        # Using the split() to fill a list with al the teams and corresponding ratings
        teams_temp = temp_line.split(',')
        # Appending only the first value to the teams list
        teams.append(teams_temp.pop(0))
    # Removing the first item, which is "team"
    teams.pop(0)
    for team in teams:
        counts[team] = 0
    # Closing the file and returning the dictionary
    file.close()
    return counts


if __name__ == "__main__":
    main()

