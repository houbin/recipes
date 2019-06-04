import random

player_win=0
banker_win=0
for i in range(1, 1000000):
    x = random.randint(1, 6)
    y = random.randint(1, 6)
    #print(x)

    if x + y == 7 or x + y == 11:
        #print('玩家win: %d %d' %(x, y))
        player_win += 1
    elif x + y == 2 or x + y == 3 or x + y == 12:
        #print('庄家win: %d %d' %(x, y))
        banker_win += 1
    else:
        sum = x + y
        while True:
            i = random.randint(1, 6)
            j = random.randint(1, 6)

            if i + j == sum:
                #print('玩家win: %d %d, sum %d' %(i, j, sum))
                player_win += 1
                break
            elif i + j == 7:
                #print('庄家win: %d %d, sum %d' %(i, j, sum))
                banker_win += 1
                break
            #else:
                #print('drawn game: %d %d, sum %d' %(i, j, sum))


print('player: %d, banker: %d' %(player_win, banker_win))
