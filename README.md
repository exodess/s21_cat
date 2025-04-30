
# s21_cat - new version of the cat utility

Developed by versiese for the SimpleBash project at School21

## Installation

1. Clone this repository

```bash
git clone https://github.com/exodess/s21_cat
```

2. Go to the project folder

```bash
cd s21_cat/
```

 3. Build the project using make
```bash
make
```
4. Update aliases
```bash
source ~/.$(echo $SHELL | cut -f 3 -d "/")rc
```

## Testing

There is a bash script in the project folder that can be used to compare the operation of s21_cat with the cat command

Running the test:
```bash
make test
```

## System information

Version: 1.0
Developed by [exodes](https://t.me/exodesk)

