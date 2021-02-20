def cprint(string, *args, style=None, fore=None, back=None, sep=' ', end='\n', file=None, level='normal'):
    style_dict = {'default': 0, 'highlight': 1, 'notbold': 22, 'underline': 4,
                  'notunderline': 24, 'blink': 5, 'notblink': 25, 'reverse': 7, 'notreverse': 27}
    color_dict = {'black': 0, 'red': 1, 'green': 2, 'yellow': 3,
                  'blue': 4, 'magenta': 5, 'cyan': 6, 'white': 7}
    if type(style) == str:
        style = style_dict[style]
    else:
        style = 0
    if type(fore) == str:
        fore = ';' + str(color_dict[fore] + 30)
    else:
        fore = ''
    if type(back) == str:
        back = ';' + str(color_dict[back] + 40)
    else:
        back = ''
    if back != '' and fore == '':
        fore = '0'
    print('\033[{}{}{}m'.format(style, fore, back), end='')
    if level == 'normal':
        print(string, *args, sep=sep, end=end, file=file)
    elif level == 'info':
        print('[info] ', string, *args, sep=sep, end=end, file=file)
    print('\033[0m', end='')


def print_an(an, style=None, fore=None, back=None, sep=' ', end='\n', file=None, level='normal'):
    args = {'style': style, 'fore': fore, 'back': back, 'sep': sep, 'end': end, 'file': file, 'level': level}
    cprint('\trrname: ', an.rrname, **args)
    cprint('\ttype: ', an.type, **args)
    cprint('\trclass: ', an.rclass, **args)
    cprint('\trdlen: ', an.rdlen, **args)
    cprint('\trdata{}: '.format(type(an.rdata)), an.rdata, **args)


def print_answer(answer, style=None, fore=None, back=None, sep=' ', end='\n', file=None, level='normal'):
    args = {'style': style, 'fore': fore, 'back': back, 'sep': sep, 'end': end, 'file': file, 'level': level}
    cprint('\t', answer, **args)
    if answer.an:
        cprint('\trrname: ', answer.an.rrname, **args)
        cprint('\ttype: ', answer.an.type, **args)
        cprint('\trclass: ', answer.an.rclass, **args)
        cprint('\trdlen: ', answer.an.rdlen, **args)
        cprint('\trdata{}: '.format(type(answer.an.rdata)), answer.an.rdata, **args)

