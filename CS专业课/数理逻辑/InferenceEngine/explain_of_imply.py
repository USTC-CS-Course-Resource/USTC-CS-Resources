from formula import *


def get_truth_value(f, explain_imp: list):
    """
    :param f: 待求真值的公式
    :param explain_imp: p->q中, (p,q)值为(0,0),(0,1),(1,0),(1,1)时的真值
    :return:
    """
    if len(explain_imp) != 4:
        return

    def confirm(_exp, assignment: dict):
        form = get_form(_exp)
        if form == 'imp':
            first = confirm(_exp[0], assignment)
            second = confirm(_exp[2], assignment)
            if not first and not second:
                return explain_imp[0]
            elif not first and second:
                return explain_imp[1]
            elif first and not second:
                return explain_imp[2]
            else:
                return explain_imp[3]
        elif form == 'not':
            return not confirm(_exp[1], assignment)
        else:
            return assignment[_exp]

    variables = f.get_variables()
    true_assignments = []
    truth_value = True
    for i in range(2 ** len(variables)):
        tmp = i
        value = []
        for j in range(len(variables)):
            value = [tmp % 2] + value
            tmp >>= 1
        assignment = dict(zip(variables, value))
        if not confirm(f.exp, assignment):
            truth_value = False
        else:
            true_assignments.append(assignment)

    return truth_value


l1 = Formula.from_str('p->(q->p)')
l2 = Formula.from_str('(p->(q->r))->((p->q)->(p->r))')
l3 = Formula.from_str('(!p->!q)->(q->p)')

for i in range(16):
    tmp = i
    explain_imp = []
    for j in range(4):
        explain_imp = [tmp % 2] + explain_imp
        tmp >>= 1
    if get_truth_value(l1, explain_imp) \
            and get_truth_value(l2, explain_imp) \
            and get_truth_value(l3, explain_imp):
        print('{{f->f is {}'.format(bool(explain_imp[0])))
        print(' f->t is {}'.format(bool(explain_imp[1])))
        print(' t->f is {}'.format(bool(explain_imp[2])))
        print(' t->t is {}}}'.format(bool(explain_imp[3])))
