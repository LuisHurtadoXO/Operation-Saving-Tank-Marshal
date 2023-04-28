import csv
import random
#similar concept to file reading and graph creation script that we used in CDA for cache memory
with open('tanks.csv', 'w', newline='') as file:
    writer = csv.writer(file)

    writer.writerow(['Pivot', 'Name', 'Battles', 'Damage', 'Rank', 'Win Rate'])     #set up category names


    for i in range(20000):      #generate and write the tank data rows with appropriate ranges
        pivot = i + 1
        name = f"RNG-{i+1}"
        battles = random.randint(97, 700)
        damage = random.randint(635, 3008)
        rank = random.randint(1000, 2500)
        win_rate = random.uniform(0.4, 0.65)
        win_rate_formatted = f"{win_rate*100:.2f}"
        writer.writerow([pivot, name, battles, damage, rank, win_rate_formatted])