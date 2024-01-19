import os
import subprocess


class Params:
    def __init__(self, filename, seconds, population):
        self.filename = filename
        self.seconds = str(seconds)
        self.population = str(population)
        self.program_path = '../../cmake-build-release/PEA_PROJ_3.exe'

    def params_OX(self):
        return [self.program_path, self.filename, self.seconds, self.population, "OX"]

    def params_PMX(self):
        return [self.program_path, self.filename, self.seconds, self.population, "PMX"]


ftv47 = '../../RESOURCES/ftv47.xml'
ftv170 = '../../RESOURCES/ftv170.xml'
rbg403 = '../../RESOURCES/rbg403.xml'


def run_program(params):
    for i in range(10):
        print(params[1::], i)
        subprocess.run(params)


# 120
def run_47_ox(population):
    run_program(Params(ftv47, 120, population).params_OX())


def run_47_pmx(population):
    run_program(Params(ftv47, 120, population).params_PMX())


def run_170_ox(population):
    run_program(Params(ftv170, 240, population).params_OX())


def run_170_pmx(population):
    run_program(Params(ftv170, 240, population).params_PMX())


def run_403_ox(population):
    run_program(Params(rbg403, 360, population).params_OX())


def run_403_ox(population):
    run_program(Params(rbg403, 360, population).params_PMX())


run_47_ox(200)
