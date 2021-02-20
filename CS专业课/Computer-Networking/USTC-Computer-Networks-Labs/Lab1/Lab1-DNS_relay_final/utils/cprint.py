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


def cprint_header(header, style=None, fore=None, back=None, sep=' ', end='\n', file=None, level='normal'):
    args = {'style': style, 'fore': fore, 'back': back, 'sep': sep, 'end': end, 'file': file, 'level': level}
    cprint(f'\t[header]   id: {header.msg_id}, '
           f'rcode: {header.rcode}, '
           f'qdcount: {header.qdcount}, '
           f'ancount: {header.qdcount}',
           **args)


def cprint_question(question, style=None, fore=None, back=None, sep=' ', end='\n', file=None, level='normal'):
    args = {'style': style, 'fore': fore, 'back': back, 'sep': sep, 'end': end, 'file': file, 'level': level}
    cprint(f'\t[question] qname: {question.qname}, '
           f'qtype: {question.qtype}, '
           f'qclass: {question.qclass}, '
           f'next_offset: {question.next_offset}',
           **args)


def cprint_answer(answer, style=None, fore=None, back=None, sep=' ', end='\n', file=None, level='normal'):
    args = {'style': style, 'fore': fore, 'back': back, 'sep': sep, 'end': end, 'file': file, 'level': level}
    cprint(f'\t[answer]   name: {answer.name}, '
           f'type: {answer.atype}, '
           f'class: {answer.aclass}, '
           f'ttl: {answer.ttl}, '
           f'rdlegnth: {answer.rdlength}, '
           f'rdata: {answer.rdata}',
           **args)
