def main():
    text = input("Text: ")

    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    grade = round(0.0588 * (letters * 100 / words) - 0.296 * ((sentences * 100 / words)) - 15.8)

    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print("Grade " + str(grade))

def count_letters(text):

    length = len(text)
    letters = 0

    for i in range(length):
        if text[i].isalpha():
            letters += 1

    return letters

def count_words(text):
    length = len(text)
    words = 1

    for i in range(length):
        if text[i] == ' ':
            words += 1
    return words

def count_sentences(text):
    length = len(text)
    sentences = 0
    for i in range(length):
        if text[i] in ['.', '!', '?']:
            sentences += 1
    return sentences

main()
