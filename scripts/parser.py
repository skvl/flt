#!/usr/bin/python

import getopt
import os
import sys

def main(argv):
    try:
        opts, args = getopt.getopt(argv, "ha:c:o:p:t:",[])
    except getopt.GetoptError:
        print("Arguments error")
        sys.exit(2)

    audioPath = None
    chinesePath = None
    outputPath = None
    pinyinPath = None
    translationPath = None

    for opt, arg in opts:
        if opt == '-h':
            print("parser.py -o OUTPUT -c CHINESE [-a AUDIO] [-p PINYIN] [-t TRANSlATION]")
            sys.exit()
        elif opt == '-a':
            audioPath = arg
        elif opt == '-c':
            chinesePath = arg
        elif opt == '-o':
            outputPath = arg
        elif opt == '-p':
            pinyinPath = arg
        elif opt == '-t':
            translationPath = arg

    if not outputPath:
        print('FATAL | No output path')
        sys.exit(2)

    audio = []
    chinese = []
    pinyin = []
    translation = []

    if chinesePath:
        with open(chinesePath) as f:
            for line in f:
                chinese += [line]
    else:
        print('FATAL | No path to chinese')
        sys.exit(2)

    if audioPath:
        audio = os.listdir(audioPath)
        audio.sort()
        if len(audio) != len(chinese):
            print('FATAL | Different number of sentences and audio')
            sys.exit(2)
    else:
        audio = [''] * len(chinese)

    if pinyinPath:
        with open(pinyinPath) as f:
            for line in f:
                pinyin += [line]
        if len(pinyin) != len(chinese):
            print('FATAL | Different number of sentences and pinyin')
            sys.exit(2)
    else:
        pinyin = [''] * len(chinese)

    if translationPath:
        with open(translationPath) as f:
            for line in f:
                translation += [[('RU', line.rstrip())]]
        if len(translation) != len(chinese):
            print('FATAL | Different number of sentences and translation')
            sys.exit(2)
    else:
        translation = [[('RU', 'Добавьте что-нибудь')]] * len(chinese)

    data = zip(audio, chinese, pinyin, translation)

    with open(outputPath, "w") as s:
        s.write('<?xml version = "1.0"?>\n')
        s.write('<sentences>\n')

        for audio, chinese, pinyin, translations in data:
            s.write('<sentence>\n')

            if audio:
                s.write('    <audio>%s</audio>\n' % audio)

            if pinyin:
                s.write('    <pinyin>%s</pinyin>\n' % pinyin)

            s.write('    <translations>\n')
            for lang, t in translations:
                s.write('        <translation language="%s">%s</translation>\n' % (lang, t))
            s.write('    </translations>\n')

            s.write('    <graphemes>\n')
            for grapheme in chinese.split():
                s.write('        <grapheme>%s</grapheme>\n' % grapheme)
            s.write('    </graphemes>\n')

            s.write('</sentence>\n')

        s.write('</sentences>\n')

if __name__ == "__main__":
    main(sys.argv[1:])
