# PainLang Compiler

Cílem je vytvořit takový základ jazyka, abych mohl vzít ten jazyk a vytvořit v něm překladač pro tento jazyk. 

## Použití
Po prvnvím naklonování repozitáře je nunté spustit `make clean`.

 - Vytvoření jenom parseru `make parser`.  
 - Spuštění kódu, když už **je zbuilděný parser** `make run_code TEST_FILE=./tests/cases/04.pl`. 
 - Spuštění kódu, když **není zbuilděný parser** `make run_full TEST_FILE=./tests/cases/02.pl` 

## Testování
Je nutné nejdříve vyčistit projekt a zkompilovat parser. `make test` toto udělá za vás, jinak by byla potřeba spustit: 
```bash
make clean
make parser
python3 test_runner.py
```




### Ostatní

Překladač zatím umí pouze `x86_64` pro získání executable a následné spuštění je nutné spustit tento příkaz:

```bash
nasm -f elf64 output.asm -o output.o && gcc -no-pie output.o -o output && ./output
```