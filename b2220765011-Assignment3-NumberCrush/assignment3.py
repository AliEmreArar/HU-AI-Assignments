import sys
def read_input_file():
    # Open the file specified by the first command line argument
    with open(sys.argv[1], "r") as input_file:
        lines = []
        split_lines = []

        # Read each line from the file
        for line in input_file:
            line = str(line)
            # Remove the newline character at the end of each line
            line = line.replace("\n", "")
            # Add the line to the list
            lines.append(line)

        # Split each line into a list of words and add it to the second list
        for line in lines:
            words = line.split(" ")
            split_lines.append(words)

        return split_lines

def split_reverse_columns(table):
    # Number of columns in the table
    num_of_columns = len(table[0])
    # Initialize lists for each column
    lists = [[] for _ in range(num_of_columns)]
    # Iterate over each row in reverse order
    for row in reversed(table):
        # For each cell in the row, append it to the corresponding list
        for i, cell in enumerate(row):
            lists[i].append(cell)
    # Return the lists
    return lists

def write_table(table, score):
    # Check if the table is not empty
    if len(table) != 0:
        last_liste = []
        # Iterate over each column in reverse order
        for i in range(-1, -(len(table[0]) + 1), -1):
            liste = []
            # For each row in the table, append the cell to the list
            for j in range(len(table)):
                liste.append(table[j][i])
            last_liste.append(liste)
        # Print each line
        for line in last_liste:
            line_str = ''
            for element in line:
                line_str += element + ' '
            print(line_str.rstrip())
    # Print the score
    print('\nYour score is:', score)

def input_alma(arr, score):
    # Prompt the user for input
    a = input('\nPlease enter a row and a column number:')
    # Split the input into row and column
    row, column = a.split(' ')
    row = int(row)
    column = int(column)
    # Check if the input is valid
    if 0 < row <= len(arr[0]) and 0 < column <= len(arr) and arr[column-1][-row] != ' ':
        print()
        return column - 1, -row
    else:
        # If the input is not valid, prompt the user again
        print('\nPlease enter a correct size!')
        return input_alma(arr, score)


def check_game_over(table):
    # Check if the table is not empty
    if len(table) != 0:
        n = len(table)
        m = len(table[0])
        dx = [0, 0, -1, 1]
        dy = [-1, 1, 0, 0]
        # Iterate over each cell in the table
        for i in range(n):
            for j in range(m):
                # Check each direction
                for k in range(4):
                    ni, nj = i + dx[k], j + dy[k]
                    # If the cell is within the table and is equal to the current cell
                    if 0 <= ni < n and 0 <= nj < m and table[ni][nj] == table[i][j] and table[ni][nj] != ' ' and table[i][j] != ' ':
                        # The game is not over
                        return False
    # The game is over
    return True

class MovementError(Exception):
    # Define a custom exception for invalid movements
    pass

def mark_and_remove_duplicates():
    # Initialize the score and the table
    score = 0
    table = split_reverse_columns(read_input_file())

    # Game loop
    while True:
        try:
            # Check if the game is over
            if check_game_over(table):
                write_table(table, score)
                print("\nGame Over")
                break
            else:
                write_table(table, score)
                column, row = input_alma(table, score)

                # Get the value at the selected cell
                value = table[column][row]
                dict1 = {(column, row): value}
                dict2 = {(column, row): value}
                change = True
                # Loop until no more duplicates are found
                while change:
                    # Check each cell in the dictionary
                    for i in dict1:
                        # Check each direction
                        if len(table) > i[0] >= 0 > (i[1] + 1) >= -len(table[0]) and value != ' ':
                            if value == table[i[0]][i[1] + 1]:
                                dict2[(i[0], i[1] + 1)] = value  # Check the cell above

                        if len(table) > (i[0] - 1) >= 0 > i[1] >= -len(table[0]) and value != ' ':
                            if value == table[i[0] - 1][i[1]]:
                                dict2[(i[0] - 1, i[1])] = value  # Check the cell to the left

                        if len(table) > i[0] >= 0 > (i[1] - 1) >= -len(table[0]) and value != ' ':
                            if value == table[i[0]][i[1] - 1]:
                                dict2[(i[0], i[1] - 1)] = value  # Check the cell below

                        if len(table) > (i[0] + 1) >= 0 > i[1] >= -len(table[0]) and value != ' ':
                            if value == table[i[0] + 1][i[1]]:
                                dict2[(i[0] + 1, i[1])] = value  # Check the cell to the right

                    # If no duplicates were found
                    if len(dict2) == 1:
                        print('No movement happened try again\n')
                        raise MovementError

                    # If no more duplicates can be found
                    elif dict1 == dict2:
                        change = False
                        # Update the score
                        score += len(dict2)*int(value)

                    else:
                        # Continue checking for duplicates
                        dict1 = dict2.copy()
                        change = True

                # Remove the duplicates from the table
                for j in dict1:
                    table[j[0]][j[1]] = ' '

                # Copy the table
                table_copy = table.copy()
                for listed in table_copy:
                    counter = 0
                    copy_listed = listed.copy()
                    # Remove empty cells
                    for number in copy_listed:
                        if number == ' ':
                            listed.remove(number)
                            counter += 1

                    # Add empty cells to the end of the list
                    for _ in range(counter):
                        listed.append(' ')

                    # Remove empty lists
                    if counter == len(listed):
                        table.remove(listed)
                # If the table is not empty
                if len(table) != 0:
                    # Copy the table
                    table_copy = [row[:] for row in table]
                    # Remove empty columns
                    for m in range(len(table_copy[0]) - 1, -1, -1):  # From the end to the beginning
                        sayac = 0
                        for line in table_copy:
                            if line[m] == ' ':
                                sayac += 1
                        if sayac == len(table_copy):
                            for line in table:
                                del line[m]

        except MovementError:
            # If an invalid movement was made, continue the game loop
            continue

def main():
    # Start the game
    mark_and_remove_duplicates()

if __name__ ==  "__main__":
    main()







