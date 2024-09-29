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


def solve_sudoku():
    # Open the output file specified by the second command line argument
    output_file = open(sys.argv[2], "w")
    # Get the input data
    sudoku_grid = read_input_file()
    step_counter = 1
    changes_made = True
    # Keep looping as long as there are changes being made
    while changes_made:
        changes_made = False
        # Loop through each cell in the matrix
        for row in range(9):
            for column in range(9):
                # If the cell is empty
                if sudoku_grid[row][column] == '0':

                    existing_numbers = []

                    # Add all unique numbers in the same row to the list
                    for number in sudoku_grid[row]:
                        if number != '0' and number not in existing_numbers:
                            existing_numbers.append(number)

                    # Add all unique numbers in the same column to the list
                    for row_index in range(9):
                        if sudoku_grid[row_index][column] != '0' and sudoku_grid[row_index][column] not in existing_numbers:
                            existing_numbers.append(sudoku_grid[row_index][column])

                    # Add all unique numbers in the same 3x3 square to the list
                    for square_row in range(int(row/3)*3,(int(row/3)+1)*3): #The mathematics formula find the row index number which is square members
                        for square_column in range(int(column/3)*3,(int(column/3)+1)*3): #The mathematics formula find the column index number which is square members
                            if sudoku_grid[square_row][square_column] != '0' and sudoku_grid[square_row][square_column] not in existing_numbers:
                                existing_numbers.append(sudoku_grid[square_row][square_column])

                    # If there is only one number missing
                    if len(existing_numbers) == 8:
                        existing_numbers.sort()
                        existing_numbers = list(map(int, existing_numbers))
                        missing_number = None

                        # Find the missing number
                        if existing_numbers[0] != 1:
                            missing_number = 1
                        elif existing_numbers[7] != 9:
                            missing_number = 9
                        else:
                            for number in range(1, 8):
                                if existing_numbers[number] != number + 1:
                                    missing_number = number + 1
                                    break

                        # Fill in the missing number
                        sudoku_grid[row][column] = str(missing_number)
                        existing_numbers.clear()

                        # Write the current state of the matrix to the output file
                        output_file.write('------------------\n')
                        output_file.write('Step' + ' ' + str(step_counter) + ' ' + '-' + ' ' + str(missing_number) + ' ' + '@' + ' ' + 'R' + str(row+1) + 'C' + str(column+1) + '\n')
                        output_file.write('------------------\n')

                        for line in sudoku_grid:
                            line_str = ''
                            for element in line:
                                line_str += element + ' '
                            output_file.write(line_str.rstrip() + '\n')

                        step_counter += 1

                        # If a change was made, restart the loop
                        changes_made = True
                        break

            if changes_made:
                break

    output_file.write('------------------')
    output_file.flush()
    output_file.close()

def main():
    solve_sudoku()

if __name__ ==  "__main__":
    main()
