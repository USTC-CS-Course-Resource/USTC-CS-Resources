"""
这个模块都是一些直接对list形式的公式(formula)(如[['!', 'p'], '->', 'q']表示!p->q)进行操作的函数
有的函数在Formula中会有相应封装
"""


def exp_to_str(exp: list):
    form = get_form(exp)
    if form == 'imp':
        left, sub_form = exp_to_str(exp[0])
        if sub_form == 'imp':
            left = '(' + left + ')'
        right, sub_form = exp_to_str(exp[2])
        if sub_form == 'imp':
            right = '(' + right + ')'
        return left + '->' + right, 'imp'
    elif form == 'not':
        sub, sub_form = exp_to_str(exp[1])
        if sub_form == 'imp':
            sub = '(' + sub + ')'
        return '!' + sub, 'not'
    elif form == 'var':
        return exp, 'var'
    else:
        return exp, 'any'


def get_form(exp):
    exp_len = len(exp)
    if type(exp) is list:
        if exp_len == 3 and exp[1] == '->':
            form = 'imp'
        elif exp_len == 2 and exp[0] == '!':
            form = 'not'
        else:
            form = '???'
    elif type(exp) is str:
        if exp[0] == '#':
            form = 'any'
        else:
            form = 'var'
    else:
        form = '???'
    return form


def is_tofill(exp):
    form = get_form(exp)
    if form == 'imp':
        return is_tofill(exp[0]) or is_tofill(exp[2])
    elif form == 'not':
        return is_tofill(exp[1])
    elif form == 'any':
        return True
    else:
        return False


def try_fit(exp: list, pattern: list, precise=False):
    exp_replace_dict = {}
    pattern_replace_dict = {}

    def fit_pattern(exp_sub, pattern_sub):
        exp_form = get_form(exp_sub)
        pattern_form = get_form(pattern_sub)
        if exp_form == 'any' and pattern_form == 'any' and not precise:
            ok = True
            if exp_sub in exp_replace_dict:
                ok = exp_replace_dict[exp_sub] == pattern_sub
            else:
                exp_replace_dict[exp_sub] = pattern_sub
            if pattern_sub in pattern_replace_dict:
                ok = ok and (pattern_replace_dict[pattern_sub] == exp_sub)
            else:
                pattern_replace_dict[pattern_sub] = exp_sub
            return ok
        elif exp_form == 'any' and pattern_form != 'any':
            if exp_sub in exp_replace_dict:
                return exp_replace_dict[exp_sub] == pattern_sub
            else:
                exp_replace_dict[exp_sub] = pattern_sub
                return True
        elif exp_form != 'any' and pattern_form == 'any' and not precise:
            if pattern_sub in pattern_replace_dict:
                return pattern_replace_dict[pattern_sub] == exp_sub
            else:
                pattern_replace_dict[pattern_sub] = exp_sub
                return True
        elif exp_form == pattern_form == 'var':
            return exp_sub == pattern_sub
        elif exp_form == pattern_form == 'imp':
            return fit_pattern(exp_sub[0], pattern_sub[0]) and fit_pattern(exp_sub[2], pattern_sub[2])
        elif exp_form == pattern_form == 'not':
            return fit_pattern(exp_sub[1], pattern_sub[1])
        else:
            return False

    result = fit_pattern(exp, pattern)
    return result, exp_replace_dict, pattern_replace_dict


def replace(exp: list, replace_dict: dict):
    def replace_sub(exp_sub: list):
        form = get_form(exp_sub)
        if form == 'imp':
            return [replace_sub(exp_sub[0]), '->', replace_sub(exp_sub[2])]
        elif form == 'not':
            return ['!', replace_sub(exp_sub[1])]
        elif form == 'any' and exp_sub in replace_dict:
            return replace_dict[exp_sub]
        else:
            return exp_sub

    return replace_sub(exp)