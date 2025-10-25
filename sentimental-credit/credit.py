while True:
    try:
        card = int(input("put your credit: "))
        if card >= 0:
            break
    except ValueError:
        pass

def dismantling(n):
    s = 0
    while n != 0:
        s += n % 10
        n = n // 10
    return s

def checkSum(credit):
    s = 0
    alt = False
    while credit != 0:
        digit = credit % 10
        if alt:
            digit *= 2
        s += dismantling(digit)
        credit = credit // 10
        alt = not alt
    return s % 10 == 0

if checkSum(card):
    ch = str(card)
    if len(ch) == 16 or len(ch) == 13:
        if ch[0] == '4':
            print("VISA")
        elif ch[0] == '5' and len(ch) == 16:
            if ch[1] in ['1', '2', '3', '4', '5']:
                print("MASTERCARD")
            else:
                print("INVALID")
        else:
            print("INVALID")
    elif len(ch) == 15:
        if ch[0] == '3':
            if ch[1] in ['4', '7']:
                print("AMEX")
            else:
                print("INVALID")
        else:
            print("INVALID")
    else:
        print("INVALID")
else:
    print("INVALID")



