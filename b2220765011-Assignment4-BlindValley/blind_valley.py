import sys

def read_input():
    # Read input from file
    with open(sys.argv[1], 'r') as input_file:
        value = input_file.read().split('\n')
        row_column_val = [i.split(' ') for i in value[:4]]
        tablo = [j.split(' ') for j in value[4:]]
        return row_column_val, tablo


def cell_value_control(last_tablo, row, value):

    count_H = last_tablo[row].count('H')
    if value[0][row] != '-1':
        if int(value[0][row]) != count_H:
            return False

    count_B = last_tablo[row].count('B')
    if value[1][row] != '-1':
        if int(value[1][row]) != count_B:
            return False

    return True
def control(last_tablo, value):

    counter = -1
    # Iterate over each line in the last table
    for line in last_tablo:
        counter += 1
        # Count the number of 'H' and 'B' in the line
        count_H = line.count('H')
        count_B = line.count('B')
        # If the value is not '-1', check if the count matches the value
        if value[0][counter] != '-1':
            if int(value[0][counter]) != count_H:
                return False

        if value[1][counter] != '-1':
            if int(value[1][counter]) != count_B:
                return False

    # Split the table into columns
    num_of_columns = len(last_tablo[0])
    lists = [[] for _ in range(num_of_columns)]
    for row in last_tablo:
        for i, cell in enumerate(row):
            lists[i].append(cell)

    counter = -1

    # Check the validity of each column
    for column in lists:
        counter += 1
        count_H = column.count('H')
        count_B = column.count('B')
        if value[2][counter] != '-1':
            if int(value[2][counter]) != count_H:
                return False

        if value[3][counter] != '-1':
            if int(value[3][counter]) != count_B:
                return False

    return True


def check_game_over(table):
    # Check if the game is over

    n = len(table)
    m = len(table[0])
    dx = [0, 0, -1, 1]
    dy = [-1, 1, 0, 0]
    # Iterate over each cell in the table
    for i in range(n):
        for j in range(m):
            if table[i][j] == 'N':
                continue
            # Check each direction
            for k in range(4):
                ni, nj = i + dx[k], j + dy[k]
                # If the cell is within the table and is equal to the current cell
                if 0 <= ni < n and 0 <= nj < m and table[ni][nj] == table[i][j]:
                    # The game is not over
                    return False
    # The game is over
    return True


def cell_control(last_tablo, row, col):
    # Check if the cell is valid

    n = len(last_tablo)
    m = len(last_tablo[0])
    dx = [0, 0, -1, 1]
    dy = [-1, 1, 0, 0]

    for k in range(4):
        ni, nj = row + dx[k], col + dy[k]
        # If the cell is within the table and is equal to the current cell
        if 0 <= ni < n and 0 <= nj < m and last_tablo[ni][nj] == last_tablo[row][col]:
            return False
    return True


def empty_counter(last_tablo):
    # Check if there are any empty cells in the table

    for line in last_tablo:
        if ' ' in line:
            return False
    return True


def solve(last_tablo, tablo, value):

    # If there are no empty cells in the last table
    if empty_counter(last_tablo):
        # If the game is over and the last table is valid
        if check_game_over(last_tablo) and control(last_tablo, value):
            return True
        return False

    # Iterate over each cell in the table
    for row in range(len(tablo)):
        for col in range(len(tablo[0])):
            cell = tablo[row][col]

            if cell == 'U' or cell == 'L':

                if last_tablo[row][col] == ' ':
                    # Try each possible value for the cell
                    for test in ['H', 'B', 'N']:

                        if cell == 'L':
                            # Try placing 'H' and 'B' in the cell and the next cell
                            if test == 'H':
                                last_tablo[row][col], last_tablo[row][col + 1] = test, 'B'
                                # If the cell is valid
                                if cell_control(last_tablo, row, col) and cell_control(last_tablo, row, col+1):
                                    if empty_counter(last_tablo):
                                        if cell_value_control(last_tablo, row, value):        #YANINDAKİ DEĞERİ DE CHECKLET

                                            if solve(last_tablo, tablo, value):
                                                return True

                                        else:
                                            continue
                                    else:
                                        if solve(last_tablo, tablo, value):
                                            return True
                                else:
                                    continue
                                # Revert the cell to empty
                                last_tablo[row][col], last_tablo[row][col + 1] = ' ', ' '

                            # Try placing 'B' and 'H' in the cell and the next cell
                            elif test == 'B':
                                last_tablo[row][col], last_tablo[row][col + 1] = test, 'H'
                                # If the cell is valid
                                if cell_control(last_tablo, row, col) and cell_control(last_tablo, row, col+1):
                                    if empty_counter(last_tablo):
                                        if cell_value_control(last_tablo, row, value):

                                            if solve(last_tablo, tablo, value):
                                                return True

                                        else:
                                            continue
                                    else:
                                        if solve(last_tablo, tablo, value):
                                            return True
                                else:
                                    continue

                                last_tablo[row][col], last_tablo[row][col + 1] = ' ', ' '

                            # Try placing 'N' in the cell and the next cell
                            else:
                                last_tablo[row][col], last_tablo[row][col + 1] = test, test

                                if solve(last_tablo, tablo, value):
                                    return True

                                last_tablo[row][col], last_tablo[row][col + 1] = ' ', ' '
                                return False

                        # If the cell is 'U'
                        elif cell == 'U':
                            # Try placing 'H' and 'B' in the cell and the cell below
                            if test == 'H':
                                last_tablo[row][col], last_tablo[row + 1][col] = test, 'B'
                                # If the cell is valid
                                if cell_control(last_tablo, row, col) and cell_control(last_tablo, row+1, col):
                                    if empty_counter(last_tablo):
                                        if cell_value_control(last_tablo, row, value):

                                            if solve(last_tablo, tablo, value):
                                                return True

                                        else:
                                            continue
                                    else:
                                        if solve(last_tablo, tablo, value):
                                            return True
                                else:
                                    continue

                                last_tablo[row][col], last_tablo[row + 1][col] = ' ', ' '

                            # Try placing 'B' and 'H' in the cell and the cell below
                            elif test == 'B':
                                last_tablo[row][col], last_tablo[row + 1][col] = test, 'H'
                                # If the cell is valid
                                if cell_control(last_tablo, row, col) and cell_control(last_tablo, row+1, col):
                                    if empty_counter(last_tablo):
                                        if cell_value_control(last_tablo, row, value):

                                            if solve(last_tablo, tablo, value):
                                                return True

                                        else:
                                            continue
                                    else:
                                        if solve(last_tablo, tablo, value):
                                            return True
                                else:
                                    continue

                                last_tablo[row][col], last_tablo[row + 1][col] = ' ', ' '

                            # Try placing 'N' in the cell and the cell below
                            else:
                                last_tablo[row][col], last_tablo[row + 1][col] = test, test

                                if solve(last_tablo, tablo, value):
                                    return True

                                last_tablo[row][col], last_tablo[row + 1][col] = ' ', ' '
                                return False
    return False


def main():
    value, tablo = read_input()

    output_file = open(sys.argv[2], 'w')
    # Create last_tablo
    last_tablo = [[] for _ in range(len(tablo))]
    for i in range(len(tablo)):
        for j in range(len(tablo[0])):
            last_tablo[i].append(' ')

    # Write output
    if solve(last_tablo, tablo, value):
        for i, line in enumerate(last_tablo):
            line_str = ''
            for element in line:
                line_str += element + ' '

            if i != len(last_tablo) - 1:
                output_file.write(line_str.rstrip() + '\n')

            else:
                output_file.write(line_str.rstrip())

    else:
        output_file.write('No solution!')

    output_file.flush()
    output_file.close()


if __name__ == "__main__":
    main()



