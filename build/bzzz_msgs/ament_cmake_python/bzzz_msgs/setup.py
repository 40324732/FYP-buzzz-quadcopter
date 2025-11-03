from setuptools import find_packages
from setuptools import setup

setup(
    name='bzzz_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('bzzz_msgs', 'bzzz_msgs.*')),
)
