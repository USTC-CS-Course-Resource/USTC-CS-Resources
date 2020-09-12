from pyparsing import *
from copy import *
from enum import Enum, unique
from typing import *
from list_formula import *


Var = Word(alphas + '#', nums + alphas + '_')
exp_parser = infixNotation(Var, [('!', 1, opAssoc.RIGHT), ('->', 2, opAssoc.LEFT)])


@unique
class FormulaState(Enum):
    todo = 0    # 待确定
    l1 = 1      # 由L1得到
    l2 = 2      # 由L2得到
    l3 = 3      # 由L3得到
    mp = 4      # 由MP规则得到
    known = 5   # 已知前提集或能够从前提集推出


class Formula:
    any_count = 0

    def __init__(self, exp=None):
        self.exp = exp
        self.first = None
        self.whole = None
        self.state = FormulaState.todo
        self.index = -1

    def try_fit(self, pattern_formula, precise=False, inplace=False, state=FormulaState.todo):
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

        result = fit_pattern(self.exp, pattern_formula.exp)
        if inplace and result:
            self.__dict__.update(pattern_formula.__dict__)
            # self.replace(pattern_replace_dict, inplace=True)
        return result, exp_replace_dict, pattern_replace_dict

    def replace(self, replace_dict: dict, inplace=False):
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
        if inplace:
            self.exp = replace_sub(self.exp)
        return self

    def try_as_l1_2(self):
        # L1后件
        if get_form(self.exp) == 'imp':
            self.first = Formula(self.exp[2])
            self.whole = Formula(self.exp[2]) >> self
            self.whole.state = FormulaState.l1
            self.state = FormulaState.mp
            # print('\tL1后件', self.whole)
            return True, {}, {}
        else:
            return False, {}, {}

    def try_as_l2_2(self):
        exp_replace_dict = {}
        pattern_replace_dict = {}
        if get_form(self.exp) == 'imp':
            p, q, r = None, None, None
            form0 = get_form(self.exp[0])
            form2 = get_form(self.exp[2])
            if form0 == 'imp' and form2 == 'imp' \
                    and self.exp[0][0] == self.exp[2][0]:
                p = Formula(self.exp[0][0])
                q = Formula(self.exp[0][2])
                r = Formula(self.exp[2][2])
            elif form0 == 'any' and form2 == 'imp':
                p = Formula(self.exp[2][0])
                q = Formula.create_any()
                r = Formula(self.exp[2][2])
                exp_replace_dict = {self.exp[0]: (p >> q).exp}
            elif form0 == 'imp' and form2 == 'any':
                p = Formula(self.exp[0][0])
                q = Formula(self.exp[0][2])
                r = Formula.create_any()
                exp_replace_dict = {self.exp[2]: (p >> r).exp}
            elif form0 == 'any' and form2 == 'any':
                # TODO: 这种情况似乎意义不大, 先跳过
                return False, {}, {}
            else:
                return False, {}, {}
            self.first = p >> (q >> r)
            self.whole = (p >> (q >> r)) >> ((p >> q) >> (p >> r))
            self.whole.state = FormulaState.l2
            self.state = FormulaState.mp
            return True, exp_replace_dict, {}
        return False, {}, {}

    def try_as_l2_22(self):
        if self.form == 'imp':
            p = Formula(self.exp[0])
            r = Formula(self.exp[2])
            q = Formula.create_any()
            self.state = FormulaState.mp
            self.first = p >> q
            self.first.state = FormulaState.todo
            self.whole = (p >> q) >> (p >> r)
            self.whole.state = FormulaState.mp
            self.whole.first = p >> (q >> r)
            self.whole.first.state = FormulaState.todo
            self.whole.whole = (p >> (q >> r)) >> ((p >> q) >> (p >> r))
            self.whole.whole.state = FormulaState.l2
            # print('\tL2后件的后件', self.whole.whole)
            return True
        return False

    def try_as_l2_222(self):
        p = Formula.create_any()
        q = Formula.create_any()
        r = self
        self.state = FormulaState.mp
        self.first = p
        self.first.state = FormulaState.todo
        self.whole = p >> r
        self.whole.state = FormulaState.mp
        self.whole.first = p >> q
        self.whole.first.state = FormulaState.todo
        self.whole.whole = (p >> q) >> (p >> r)
        self.whole.whole.state = FormulaState.mp
        self.whole.whole.first = p >> (q >> r)
        self.whole.whole.first.state = FormulaState.todo
        self.whole.whole.whole = (p >> (q >> r)) >> ((p >> q) >> (p >> r))
        self.whole.whole.whole.state = FormulaState.l2
        # print('\tL2后件的后件的后件', self.whole.whole)
        return True

    def try_as_l3_2(self):
        if self.form == 'imp':
            q = Formula(self.exp[0])
            p = Formula(self.exp[2])
            self.state = FormulaState.mp
            self.first = ~p >> ~q
            self.first.state = FormulaState.todo
            self.whole = (~p >> ~q) >> (q >> p)
            self.whole.state = FormulaState.l3
            # print('l3的后件')
            return True
        return False

    def try_as_l3_22(self):
        self.state = FormulaState.mp
        p = self
        q = Formula.create_any()
        self.first = q
        self.first.state = FormulaState.todo
        self.whole = q >> p
        self.whole.state = FormulaState.mp
        self.whole.first = ~p >> ~q
        self.whole.first.state = FormulaState.todo
        self.whole.whole = (~p >> ~q) >> (q >> p)
        self.whole.whole.state = FormulaState.l3
        # print('l3的后件的后件')
        return True

    def process_str(self):
        """
        :return: the str for print the process
        """
        return '({index:3d}°)\t{exp}\t[{sub}]'.format(index=self.index,
                                                    exp=str(self),
                                                    sub=self.come_from)

    def get_variables(self):
        exps = [self.exp]
        variables = set()
        while len(exps) > 0:
            exp = exps[0]
            exps = exps[1:]
            if get_form(exp) == 'imp':
                exps += [exp[0], exp[2]]
            elif get_form(exp) == 'not':
                exps.append(exp[1])
            elif get_form(exp) == 'var' or get_form(exp) == 'any':
                variables |= {exp}
        variables = list(variables)
        variables.sort()
        return variables

    def get_truth_value_with_assign(self, assign: dict):
        def confirm(_exp, assignment: dict):
            form = get_form(_exp)
            if form == 'imp':
                return (not confirm(_exp[0], assignment)) or confirm(_exp[2], assignment)
            elif form == 'not':
                return not confirm(_exp[1], assignment)
            else:
                return assignment[_exp]
        return confirm(self.exp, assignment=assign)

    def get_truth_value(self):
        """
        :return: 公式真值
        """
        def confirm(_exp, assignment: dict):
            form = get_form(_exp)
            if form == 'imp':
                return (not confirm(_exp[0], assignment)) or confirm(_exp[2], assignment)
            elif form == 'not':
                return not confirm(_exp[1], assignment)
            else:
                return assignment[_exp]

        variables = self.get_variables()
        true_assignments = []
        truth_value = True
        for i in range(2**len(variables)):
            tmp = i
            value = []
            for j in range(len(variables)):
                value = [tmp % 2] + value
                tmp >>= 1
            assignment = dict(zip(variables, value))
            if not confirm(self.exp, assignment):
                truth_value = False
            else:
                true_assignments.append(assignment)

        return truth_value, true_assignments

    def get_truth_value_with_premise(self, premise_set=None):
        """
        :return: 公式真值
        """
        if not premise_set:
            premise_set = []

        variables = self.get_variables()
        truth_value, true_assignment = self.get_truth_value()
        premise_true_assignment = []
        for i in range(2**len(variables)):
            tmp = i
            value = []
            for j in range(len(variables)):
                value = [tmp % 2] + value
                tmp >>= 1
            assignment = dict(zip(variables, value))
            premise_true_assignment.append(assignment)
        for f in premise_set:
            f_truth_value, f_true_assignment = f.get_truth_value()
            if f_truth_value:
                continue
            else:
                new_premise_true_assignment = []
                for assign in premise_true_assignment:
                    if assign in f_true_assignment:
                        new_premise_true_assignment.append(assign)
                premise_true_assignment = new_premise_true_assignment

        for assign in premise_true_assignment:
            if not self.get_truth_value_with_assign(assign):
                return False
        return True

    @property
    def imp_and_layer_num(self):
        imp_num = 0

        def num_sub(exp, l_num):
            nonlocal imp_num
            form = get_form(exp)
            if form == 'imp':
                imp_num += 1
                return max(num_sub(exp[0], l_num + 1), num_sub(exp[2], l_num + 1))
            elif form == 'not':
                return num_sub(exp[1], l_num)
            return l_num
        return imp_num, num_sub(self.exp, 0)

    @property
    def come_from(self):
        _come_from = self.state.name
        if self.state == FormulaState.mp:
            _come_from = 'MP {}°, {}°'.format(self.first.index, self.whole.index)
        return _come_from

    @property
    def form(self):
        return get_form(self.exp)

    @property
    def tofill(self):
        def is_tofill_sub(exp):
            form = get_form(exp)
            if form == 'imp':
                return is_tofill(exp[0]) or is_tofill(exp[2])
            elif form == 'not':
                return is_tofill(exp[1])
            elif form == 'any':
                return True
            else:
                return False
        return is_tofill_sub(self.exp)

    @staticmethod
    def from_str(exp_str, state=FormulaState.todo):
        new_f = Formula(exp_parser.parseString(exp_str).asList()[0])
        new_f.state = state
        return new_f

    @staticmethod
    def create_any():
        new_f = Formula('#{}'.format(Formula.any_count % 1000))
        Formula.any_count += 1
        new_f.state = FormulaState.todo
        return new_f

    @staticmethod
    def create_l1_pattern():
        Formula.any_count += 2
        new_f = Formula.from_str('#{f1}->(#{f2}->#{f1})'.format(f1=Formula.any_count - 2,
                                                                f2=Formula.any_count - 1))
        new_f.state = FormulaState.l1
        return new_f

    @staticmethod
    def create_l2_pattern(p=None, q=None, r=None):
        p = Formula('#{}'.format(Formula.any_count)) if p is None else str(p)
        Formula.any_count += 1
        q = Formula('#{}'.format(Formula.any_count)) if q is None else str(q)
        Formula.any_count += 1
        r = Formula('#{}'.format(Formula.any_count)) if r is None else str(r)
        Formula.any_count += 1
        new_f = (p >> (q >> r)) >> ((p >> q) >> (p >> r))
        new_f.state = FormulaState.l2
        return new_f

    @staticmethod
    def create_l3_pattern():
        Formula.any_count += 2
        new_f = Formula.from_str('(!#{f1}->!#{f2})->(#{f2}->#{f1})'.format(f1=Formula.any_count - 2,
                                                                           f2=Formula.any_count - 1))
        new_f.state = FormulaState.l3
        return new_f

    def __rshift__(self, other):
        new_f = Formula([self.exp, '->', other.exp])
        return new_f

    def __invert__(self):
        new_f = Formula(['!', self.exp])
        return new_f

    def __str__(self):
        return exp_to_str(self.exp)[0]


# 直接设123可能导致一些问题
l1_pattern = Formula.from_str('#1->(#2->#1)')
l2_pattern = Formula.from_str('(#1->(#2->#3))->((#1->#2)->(#1->#3))')
l3_pattern = Formula.from_str('(!#1->!#2)->(#2->#1)')