# Анализ горячих клавиш и модификаторов в physiXournalpp

## Часть 1. Действия, выполняемые при помощи сочетаний клавиш

### 1.1. Акселераторы из ActionProperties.h (C++ код, с учётом платформы)

Все акселераторы задаются в `ActionProperties.h` и устанавливаются программно через `gtk_application_set_accels_for_action`. Используется псевдоним `<Primary>`, который GTK автоматически преобразует: на macOS → Cmd, на Linux/Windows → Ctrl.

| Сочетание | Действие | Action |
|---|---|---|
| `Primary+N` (macOS: Cmd+N, Linux/Win: Ctrl+N) | Новый файл | `win.new-file` |
| `Primary+O` | Открыть | `win.open` |
| `Primary+S` | Сохранить | `win.save` |
| `Primary+Shift+S` | Сохранить как | `win.save-as` |
| `Primary+E` | Экспорт как... | `win.export-as` |
| `Primary+P` | Печать | `win.print` |
| `Primary+Q` | Выход | `app.quit` |
| `Primary+Z` | Отменить | `win.undo` |
| `Primary+Shift+Z` / `Primary+Y` | Повторить | `win.redo` |
| `Primary+X` | Вырезать | `win.cut` |
| `Primary+C` | Копировать | `win.copy` |
| `Primary+V` | Вставить | `win.paste` |
| `Primary+F` | Найти | `win.search` |
| `Primary+A` | Выделить всё | `win.select-all` |
| `Delete` | Удалить | `win.delete` |
| `Primary++` / `Primary+=` | Приблизить | `win.zoom-in` |
| `Primary+-` | Отдалить | `win.zoom-out` |
| `Primary+Home` | Первая страница | `win.goto-first` |
| `Primary+Page_Up` | Предыдущая страница | `win.goto-previous` |
| `Primary+G` | Перейти к странице | `win.goto-page` |
| `Primary+Page_Down` | Следующая страница | `win.goto-next` |
| `Primary+End` | Последняя страница | `win.goto-last` |
| `Primary+Shift+Page_Down` | Следующая аннотированная страница | `win.goto-next-annotated-page` |
| `Primary+Shift+Page_Up` | Предыдущая аннотированная страница | `win.goto-previous-annotated-page` |
| `Primary+D` | Новая страница после текущей | `win.new-page-after` |
| `Primary+Shift+Delete` | Удалить страницу | `win.delete-page` |
| `Primary+L` | Добавить слой выше активного | `win.layer-new-above-current` |
| `Primary+Shift+L` | Удалить слой | `win.layer-delete` |
| `Primary+M` | Объединить слой вниз | `win.merge-layer-down` |
| `Primary+R` | Переименовать слой | `win.layer-rename` |
| `Shift+Page_Down` | Предыдущий слой | `win.layer-goto-previous` |
| `Shift+Page_Up` | Следующий слой | `win.layer-goto-next` |
| `Primary+Shift+P` | Выбрать перо | `win.select-tool` (target=TOOL_PEN) |
| `Primary+Shift+E` | Выбрать ластик | `win.select-tool` (target=TOOL_ERASER) |
| `Primary+Shift+W` | Выбрать линейный текст PDF | `win.select-tool` (target=TOOL_SELECT_PDF_TEXT_LINEAR) |
| `Primary+Shift+Y` | Выбрать текст в прямоугольнике PDF | `win.select-tool` (target=TOOL_SELECT_PDF_TEXT_RECT) |
| `Primary+Shift+H` | Выбрать маркер | `win.select-tool` (target=TOOL_HIGHLIGHTER) |
| `Primary+Shift+T` | Выбрать текст | `win.select-tool` (target=TOOL_TEXT) |
| `Primary+Shift+I` | Выбрать изображение | `win.select-tool` (target=TOOL_IMAGE) |
| `Primary+Shift+R` | Выделение прямоугольником | `win.select-tool` (target=TOOL_SELECT_RECT) |
| `Primary+Shift+G` | Выделение области | `win.select-tool` (target=TOOL_SELECT_REGION) |
| `Primary+Shift+O` | Выделение объекта | `win.select-tool` (target=TOOL_SELECT_OBJECT) |
| `Primary+Shift+V` | Вертикальное пространство | `win.select-tool` (target=TOOL_VERTICAL_SPACE) |
| `Primary+Shift+A` | Инструмент "Рука" | `win.select-tool` (target=TOOL_HAND) |
| `Primary+Shift+D` | Инструмент по умолчанию | `win.select-default-tool` |
| `Primary+1` | Распознаватель фигур | `win.tool-draw-shape-recognizer` |
| `Primary+2` | Прямоугольник | `win.tool-draw-rectangle` |
| `Primary+3` | Эллипс / Косинус | `win.tool-draw-ellipse` / `win.tool-draw-cosine` |
| `Primary+4` | Стрелка | `win.tool-draw-arrow` |
| `Primary+5` | Двойная стрелка | `win.tool-draw-double-arrow` |
| `Primary+6` | Система координат | `win.tool-draw-coordinate-system` |
| `Primary+7` | Линия | `win.tool-draw-line` |
| `Primary+8` | Сплайн | `win.tool-draw-spline` |
| `Primary+Shift+F` | Шрифт текста... | `win.select-font` |
| `Primary+Shift+X` | Добавить/редактировать TeX | `win.tex` |
| `F5` | Режим презентации | `win.presentation-mode` |
| `F9` | Показать панели инструментов | `win.show-toolbar` |
| `F10` | Показать меню | `win.show-menubar` |
| `F11` | Полноэкранный режим | `win.fullscreen` |
| `F12` | Показать боковую панель | `win.show-sidebar` |


### 1.3. Акселераторы из TextEditorKeyBindings.h (текстовый редактор)

Эти биндинги работают только когда активен текстовый редактор (ввод текста).

| Сочетание | Действие |
|---|---|
| `←` / `→` | Переместить курсор на символ |
| `Ctrl+←` / `Ctrl+→` | Переместить курсор на слово |
| `↑` / `↓` | Переместить курсор на строку |
| `Ctrl+↑` / `Ctrl+↓` | Переместить курсор на абзац |
| `Home` / `End` | В начало/конец строки |
| `Ctrl+Home` / `Ctrl+End` | В начало/конец текста |
| `Page_Up` / `Page_Down` | На страницу вверх/вниз |
| `Ctrl+Page_Up` / `Ctrl+Page_Down` | На страницу влево/вправо |
| `Ctrl+A` | Выделить всё |
| `Delete` | Удалить символ после курсора |
| `Backspace` | Удалить символ перед курсором |
| `Ctrl+Delete` | Удалить слово после курсора |
| `Ctrl+Backspace` | Удалить слово перед курсором |
| `Ctrl+Shift+Delete` | Удалить до конца абзаца |
| `Ctrl+Shift+Backspace` | Удалить до начала абзаца |
| `Ctrl+X` / `Shift+Delete` | Вырезать |
| `Ctrl+C` / `Ctrl+Insert` | Копировать |
| `Ctrl+V` / `Shift+Insert` | Вставить |
| `Insert` | Переключить режим замены |
| `Ctrl+B` | Жирный текст |
| `Ctrl++` / `Ctrl+KP_Add` | Увеличить размер шрифта |
| `Ctrl+-` / `Ctrl+KP_Subtract` | Уменьшить размер шрифта |
| `Enter` | Новая строка |
| `Tab` | Табуляция |

### 1.4. Обработка клавиш в XournalView::onKeyPressEvent (ручная)

Эти клавиши обрабатываются вручную, без использования GTK акселераторов.

| Клавиша | Модификатор | Действие |
|---|---|---|
| `C` | `Ctrl` | Копировать выделенный PDF текст (только если есть выделение PDF) |
| `Escape` | — | Снять выделение |
| `← ↑ → ↓` | — | Переместить выделение на 3px |
| `← ↑ → ↓` | `Alt` | Переместить выделение на 1px |
| `← ↑ → ↓` | `Shift` | Переместить выделение на 10px |
| `Page_Down` / `KP_Page_Down` | — | Следующая страница |
| `Page_Up` / `KP_Page_Up` | — | Предыдущая страница |
| `Space` | — | Прокрутка вниз |
| `Space` | `Shift` | Прокрутка вверх |
| `KP_Up/Down/Left/Right` | — | Навигация по страницам (сетка) |
| `↑` / `K` / `k` | — | Прокрутка вверх (или предыдущая страница в режиме презентации) |
| `↑` / `K` / `k` | `Shift` | На страницу выше (сетка) |
| `↓` / `J` / `j` | — | Прокрутка вниз (или следующая страница в режиме презентации) |
| `↓` / `J` / `j` | `Shift` | На страницу ниже (сетка) |
| `←` / `H` / `h` | — | Прокрутка влево (или предыдущая страница в режиме презентации) |
| `←` / `H` / `h` | `Shift` | На страницу левее (сетка) |
| `→` / `L` / `l` | — | Прокрутка вправо (или следующая страница в режиме презентации) |
| `→` / `L` / `l` | `Shift` | На страницу правее (сетка) |
| `End` / `KP_End` | — | Последняя страница |
| `Home` / `KP_Home` | — | Первая страница |
| `0`-`9` | — | Выбрать цвет (по индексу в палитре) |

### 1.5. Обработка клавиш в GeometryToolInputHandler::keyPressed

Эти клавиши работают только когда активен геометрический инструмент (угольник/циркуль).

| Клавиша | Модификатор | Действие |
|---|---|---|
| `← ↑ → ↓` | — | Переместить инструмент на 0.5 см |
| `← ↑ → ↓` | `Alt` | Переместить инструмент на 0.05 см |
| `← ↑ → ↓` | `Shift` | Переместить инструмент вдоль его угла поворота |
| `R` | — | Повернуть по часовой на 5° |
| `R` | `Alt` | Повернуть по часовой на 0.2° |
| `r` | — | Повернуть против часовой на 5° |
| `r` | `Alt` | Повернуть против часовой на 0.2° |
| `S` | — | Уменьшить масштаб (÷1.1) |
| `S` | `Alt` | Уменьшить масштаб (÷1.01) |
| `s` | — | Увеличить масштаб (×1.1) |
| `s` | `Alt` | Увеличить масштаб (×1.01) |
| `m` | — | Отметить начало координат |

---

## Часть 2. Как модификаторы меняют поведение мыши, стилуса и скролла

### 2.1. Модификаторы при рисовании (BaseShapeHandler)

При рисовании фигур (прямоугольник, эллипс, линия, стрелка и т.д.) модификаторы меняют поведение через `updateShape(isAltDown, isShiftDown, isControlDown)`:

| Модификатор | Эффект |
|---|---|
| `Shift` | Меняет поведение в зависимости от `flipShift` (настраивается): обычно **фиксирует пропорции** (квадрат вместо прямоугольника, круг вместо эллипса) или **фиксирует угол** (45°) |
| `Control` | Меняет поведение в зависимости от `flipControl`: обычно **включает/отключает привязку к сетке** (snap to grid) |
| `Alt` | Обычно **включает/отключает привязку к сетке** (snap to grid) — работает как toggle |

### 2.2. Модификаторы при скролле (ZoomControl)

Обработчик `onScrolledwindowMainScrollEvent`:

| Модификатор | Эффект |
|---|---|
| `Ctrl` + Scroll | **Приближение/отдаление** (zoom in/out) |
| `Shift` + Scroll | **Горизонтальная прокрутка** (стандартное поведение GTK) |
| `Alt` + Scroll | **Игнорируется** (чтобы не конфликтовать с Compiz и другими оконными менеджерами) |
| `Ctrl+Shift` + Scroll | **Игнорируется** (только чисто Ctrl или чисто Shift) |
| Любой другой модификатор | **Игнорируется** |

Также есть обработка **тачпад-жестов** (pinch):
- Двумя пальцами — масштабирование (независимо от модификаторов)

### 2.3. Модификаторы при нажатии кнопок мыши/стилуса

#### MouseInputHandler

| Кнопка | Эффект |
|---|---|
| Левая кнопка (1) | Начать рисование/выделение выбранным инструментом |
| Средняя кнопка (2) | Временно переключить инструмент на назначенный в настройках для `BUTTON_MOUSE_MIDDLE` |
| Правая кнопка (3) | Временно переключить инструмент на назначенный в настройках для `BUTTON_MOUSE_RIGHT` |

#### StylusInputHandler

| Кнопка/Действие | Эффект |
|---|---|
| Касание пером (button 1) | Начать рисование |
| Кнопка на стилусе 1 (button 2) | Временно переключить инструмент на `BUTTON_STYLUS_ONE` |
| Кнопка на стилусе 2 (button 3) | Временно переключить инструмент на `BUTTON_STYLUS_TWO` |
| Ластик (eraser) | Временно переключить инструмент на `BUTTON_ERASER` |
| Двойной клик (button 2/3) | Выполнить дискретное действие (double/triple press) |

### 2.4. Модификаторы при перемещении мыши/стилуса (PenInputHandler)

#### При активном выделении (selection)

| Модификатор/Кнопка | Эффект |
|---|---|
| `Shift` + клик по странице | Отменить смену выделения (для инструментов выделения) |
| `Shift` + клик | Отменить фильтр тапов (tap filter) |
| Правая кнопка (modifier3) + перетаскивание выделения | **Копировать** выделение вместо перемещения |
| `Shift` + движение (при активном выделении) | Не перемещать выделение, а рисовать поверх |

#### При движении с зажатой кнопкой

| Условие | Эффект |
|---|---|
| Инструмент "Рука" (Hand) + зажатая кнопка | Прокрутка страницы |
| `Shift` зажат + инструмент выделения | Отменить режим перемещения выделения |

### 2.5. Модификаторы при завершении штриха (PenInputHandler::actionEnd)

| Модификатор | Эффект |
|---|---|
| `Shift` + клик по кнопке удаления выделения | **Не отменять** удаление (даже если tap filter включён) |
| Без Shift + tap filter включён | Отменить штрих и выполнить тап (выделение объекта) |

### 2.6. Модификаторы в PositionInputData (передаются в обработчики страницы)

Эти модификаторы доступны в `PositionInputData` при обработке событий на странице:

| Метод | GDK маска | Физическая клавиша |
|---|---|---|
| `isShiftDown()` | `GDK_SHIFT_MASK` | Shift |
| `isControlDown()` | `GDK_CONTROL_MASK` | Control |
| `isAltDown()` | `GDK_MOD1_MASK` | Alt |

### 2.7. Фильтрация модификаторов в InputContext

В `InputContext.cpp` (строка 75-76) перед передачей события в `KeyEvent` модификаторы фильтруются:

```cpp
e.state = state & gtk_accelerator_get_default_mod_mask() & ~consumed_modifiers
```

`gtk_accelerator_get_default_mod_mask()` возвращает маску: `Ctrl | Shift | Alt | Meta | Super | Hyper`.

Это означает, что Caps Lock, Num Lock и другие "неакселераторные" модификаторы **отбрасываются**. Также отбрасываются "consumed modifiers" — модификаторы, которые были "поглощены" раскладкой клавиатуры (например, Shift для получения заглавной буквы).

---

## Известные проблемы

1. **Русская раскладка**: Все акселераторы и ручные проверки keyval не работают, т.к. keyval зависит от раскладки.
2. **TextEditorKeyBindings**: Не поддерживают Meta (Cmd) — на macOS не работают Cmd+C, Cmd+V и т.д. в текстовом редакторе.
3. **Точное сравнение state**: В `XournalView.cpp` используется `state == GDK_CONTROL_MASK` (точное равенство), а не `state & GDK_CONTROL_MASK` (проверка флага). Это значит, что `Ctrl+Shift+C` не сработает как копирование PDF текста.

## Решённые проблемы

### 1. Русская раскладка — добавлены Cyrillic keyval names как альтернативные акселераторы

Для всех акселераторов с буквами добавлены соответствующие GDK keyval names для кириллицы (по физическому положению на клавиатуре):

| Английская | Русская | GDK keyval name | Действие |
|---|---|---|---|
| `Primary+N` | `Т` | `Cyrillic_te` | Новый файл |
| `Primary+O` | `Щ` | `Cyrillic_shcha` | Открыть |
| `Primary+S` | `Ы` | `Cyrillic_yeru` | Сохранить |
| `Primary+Shift+S` | `Ы` | `Cyrillic_yeru` | Сохранить как |
| `Primary+E` | `У` | `Cyrillic_u` | Экспорт |
| `Primary+P` | `З` | `Cyrillic_ze` | Печать |
| `Primary+Q` | `Й` | `Cyrillic_shorti` | Выход |
| `Primary+Z` | `Я` | `Cyrillic_ya` | Отменить |
| `Primary+Shift+Z` | `Я` | `Cyrillic_ya` | Повторить |
| `Primary+Y` | `Н` | `Cyrillic_en` | Повторить |
| `Primary+X` | `Ч` | `Cyrillic_che` | Вырезать |
| `Primary+C` | `С` | `Cyrillic_es` | Копировать |
| `Primary+V` | `М` | `Cyrillic_em` | Вставить |
| `Primary+F` | `А` | `Cyrillic_a` | Найти |
| `Primary+A` | `Ф` | `Cyrillic_ef` | Выделить всё |
| `Primary+G` | `П` | `Cyrillic_pe` | Перейти к странице |
| `Primary+D` | `В` | `Cyrillic_ve` | Новая страница |
| `Primary+L` | `Д` | `Cyrillic_de` | Добавить слой |
| `Primary+Shift+L` | `Д` | `Cyrillic_de` | Удалить слой |
| `Primary+M` | `Ь` | `Cyrillic_softsign` | Объединить слой |
| `Primary+R` | `К` | `Cyrillic_ka` | Переименовать слой |

**Важно:** Используются GDK keyval names (например, `Cyrillic_te`), а не сами русские буквы. Это необходимо, потому что `gtk_accelerator_parse()` не понимает unicode-символы, но понимает стандартные GDK keyval names.

### 2. Платформозависимые модификаторы — заменены на `<Primary>`

Все `#ifdef __APPLE__` с `<Meta>`/`<Ctrl>` заменены на единый `<Primary>`, который GTK автоматически преобразует:
- **macOS**: `<Primary>` → `Cmd`
- **Linux/Windows**: `<Primary>` → `Ctrl`

### 3. Акселераторы перенесены из mainmenubar.xml в ActionProperties.h

Все акселераторы, которые ранее были заданы в `ui/mainmenubar.xml` через атрибут `accel`, перенесены в C++ код `ActionProperties.h`. Это позволяет:
- Использовать `<Primary>` для кроссплатформенности
- Добавлять несколько альтернативных акселераторов (включая русские буквы)
- Управлять акселераторами программно
- Избежать дублирования и путаницы
