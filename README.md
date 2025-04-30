# PainLang Compiler

Cílem je vytvořit takový základ jazyka, abych mohl vzít ten jazyk a vytvořit v něm překladač pro tento jazyk. 

## Testování
Je nutné nejdříve vyčistit projekt a zkompilovat parser. `make test` toto udělá za vás, jinak by byla potřeba spustit: 
```bash
make clean
make parser
python3 test_runner.py
```

## Použití

Vytvoření jenom parseru `make parser`. 
```
make run
```


### Ostatní

Překladač zatím umí pouze `x86_64` pro získání executable a následné spuštění je nutné spustit tento příkaz:

```bash
nasm -f elf64 output.asm -o output.o && gcc -no-pie output.o -o output && ./output
```