while True:
    try:
        height = int(input("Height: "))
        if 9 > height > 0:
            break
    except ValueError:
        pass

i = 0
while i < height:
    for k in range(height - i - 1):
        print(" ", end="")
    for k in range(i + 1):
        print("#", end="")
    print("  ", end="")
    for k in range(i + 1):
        print("#", end="")
    print()
    i += 1


