#mario phyton done in 2020, redo in 2024
#ini adalah catatan/komen

#you have to get input from user until correct
while True:
    try:
        height = int(input("Height: "))
        if (height >= 1) and (height <= 8):
            break
    except:
        print("", end="")

# print newline
for j in range(height):

    # print some spaces
    for spaces in range(height-j-1):
        print(" ", end="")

    # print some hashes
    for i in range(j+1):
        print("#", end="")

    print()
