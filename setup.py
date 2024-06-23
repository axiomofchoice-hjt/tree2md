from setuptools import setup, find_packages

setup(
    name="tree2md",
    version="1.0.0",
    packages=find_packages(),
    author="Axiomofchoice-hjt",
    author_email="1939696303@qq.com",
    long_description=open("README.md").read(),
    long_description_content_type="text/markdown",
    url="https://github.com/axiomofchoice-hjt/tree2md",
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    install_requires=[],
    entry_points={
        'console_scripts': [
            'tree2md = tree2md:main'
        ]
    }
)
