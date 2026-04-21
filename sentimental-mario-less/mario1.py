# mario pythonic version (different approach)

# get valid height
height = int(input("Height (1-8): "))

while height < 1 or height > 8:
    height = int(input("Height (1-8): "))

# print pyramid
for row in range(1, height + 1):
    spaces = " " * (height - row)
    hashes = "#" * row
    print(spaces + hashes)
