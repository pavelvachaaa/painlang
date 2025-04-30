# PainLang Language Server

Tento jazykový server poskytuje základní podporu pro jazyk **PainLang** v editorech podporujících Language Server Protocol (LSP), jako je Visual Studio Code.

## ✨ Funkce

- **Automatické doplňování**:
  - Klíčová slova jako `let`, `print`, `if`, `else`, `function`, apod.
  - Proměnné a funkce definované uživatelem.
  - Inteligentní návrhy v rámci `print(...)` a při deklaraci typu (`let x: ...`).
  - Snippety pro běžné konstrukce jako `if`, `for`, `function`, atd.

- **Nápověda při najetí kurzorem (hover)**:
  - Zobrazí podrobnosti o proměnných, funkcích, klíčových slovech i snippetech.

- **Synchronizace dokumentů**:
  - Sleduje změny v otevřených dokumentech a aktualizuje interní symbolovou tabulku.

## 🧠 Architektura
Jazykový server využívá balík vscode-languageserver a implementuje následující LSP funkce:

- onInitialize: Nastavení schopností serveru.
- onCompletion: Nabízí kontextové návrhy.
- onHover: Zobrazí dokumentaci při najetí kurzorem.
- onDidChangeContent: Parsuje dokument a aktualizuje symboly.
- onCompletionResolve: Rozšiřuje návrhy snippetů o příklady použití.

## 📄 Podporovaná klíčová slova
```
let, print, if, else, for, function, return, while, true, false, string, number, bool, include
```

## 🔧 Snippety

Například:
- if – vloží podmíněný blok
- for – vloží klasickou smyčku s proměnnou
- function – vytvoří šablonu pro definici funkce

## 🗂️ Tabulka symbolů

Proměnné a funkce jsou detekovány pomocí jednoduché analýzy textu:

Proměnné: `let jmeno : typ`
Funkce: `function nazev(parametry) -> navratovyTyp`

## 📚 Příklad kódu

```ts
let x: number = 5;
function add(a: number, b: number) -> number {
    return a + b;
}
print(add(x, 10));
```