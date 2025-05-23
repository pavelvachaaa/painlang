# PainLang Compiler

## Requirments
```
npm + node v20+ (v případě buildění langauge-serveru )
python (v případě spouštění testů)
nasm
gcc
yacc
flex
```

## Použití
Po prvním naklonování repozitáře proveďte `make clean`.

 - Pro vytvoření jenom parseru provďte `make parser`.  
 - Spuštění kódu, když už **je zbuilděný parser** `make run_code TEST_FILE=./tests/cases/04.pl`. 
 - Spuštění kódu, když **není zbuilděný parser** `make run_full TEST_FILE=./tests/cases/02.pl` 
 - Bez make filu a bez optimalizace `./bin/painlang_parser -i ./tests/valid_01.pl`
 - Bez make filu a s optimalizací `./bin/painlang_parser -i ./tests/valid_01.pl -O`


Rozdíly optimalizace a bez optimalizace jsou krásně vidět v `output.ir` a `output.asm`. 

## Language server

### Marketplace
Language server si můžete najít na extension marketplace jako `PainLang` a nebo pomocí tohoto odkazu [PainLang Language Support](https://marketplace.visualstudio.com/items?itemName=pvacha.painlang-highlighter).


### Ze zdroje
V případě buildění language-serveru ze zdroje. Je nutné mít nainstalovaný `node` a `npm package manager`. Poté stačí spustit `make languageServer` a modlit se 🙏🏾🙏🏾🙏🏾.


## Testování
Je nutné nejdříve vyčistit projekt a zkompilovat parser. `make test` toto udělá za vás, jinak by byla potřeba spustit: 
```bash
make clean
make parser
python3 test_runner.py
```

### Ostatní informace (Good to know, ale nejsou potřeba)

Překladač zatím umí pouze `x86_64` pro získání executable a následné spuštění je nutné spustit tento příkaz:

```bash
nasm -f elf64 output.asm -o output.o && gcc -no-pie output.o -o output && ./output
```