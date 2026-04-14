# 🧠 uPLC: Cómo pensar la conversión de Ladder / Bloques a C (explicado simple)

## 🎯 ¿Qué estamos haciendo realmente?

Cuando usamos uPLC, parece que estamos dibujando lógica…

Pero en realidad estamos haciendo algo mucho más interesante:

> Estamos describiendo cómo debe comportarse un sistema, y luego lo convertimos automáticamente en código ejecutable.

---

## 🔌 La analogía clave (para entenderlo de verdad)

Imaginá un circuito eléctrico tradicional:

* Tenés cables
* Tenés interruptores (contactos)
* Tenés una lámpara (salida)

Si la corriente logra llegar a la lámpara → se enciende.

👉 Eso es exactamente lo que representa Ladder.

---

## ⚡ ¿Qué hace uPLC con eso?

uPLC toma esa idea de “corriente que fluye” y la transforma en algo digital:

* Corriente → `true / false`
* Contactos → condiciones
* Bobinas → variables de salida

Entonces:

```
--[ I0 ]--[/ I1 ]----( Q0 )
```

Se convierte en:

```c
Q0 = I0 && !I1;
```

👉 No estamos dibujando… estamos definiendo lógica.

---

## 🧱 ¿Y los bloques?

Los bloques (uPLCv6Blocks) son lo mismo, pero más amigable.

En lugar de ver “cables”, ves piezas que encajan.

Pero por dentro… es exactamente igual.

```
I0 → AND → NOT(I1) → Q0
```

Resultado:

```c
Q0 = I0 && !I1;
```

👉 Ladder y Blocks son solo dos formas de expresar la misma idea.

---

## 🧾 El rol FUNDAMENTAL del JSON

Acá está el corazón de uPLC.

Entre lo que el usuario dibuja y el código final… hay un paso invisible:

> 👉 El JSON

---

## 🤔 ¿Por qué es tan importante?

Porque separa todo:

* Lo que el usuario ve (UI)
* Lo que el sistema entiende (lógica)
* Lo que finalmente se ejecuta (código C)

---

## 🧩 Ejemplo simple

Lo que dibujás:

```
--[ I0 ]--[/ I1 ]----( Q0 )
```

Se transforma internamente en algo así:

```json
{
  "rungs": [
    {
      "type": "series",
      "children": [
        {"type": "contact", "var": "I0", "mode": "NO"},
        {"type": "contact", "var": "I1", "mode": "NC"}
      ],
      "output": {"type": "coil", "var": "Q0"}
    }
  ]
}
```

Y eso después termina en:

```c
Q0 = I0 && !I1;
```

---

## 💡 La idea poderosa

Ese JSON permite algo enorme:

* Guardar proyectos
* Simular sin hardware
* Generar C (Arduino)
* Generar otros lenguajes en el futuro

👉 JSON no es un detalle… es el idioma interno de uPLC.

---

## 🌳 El árbol lógico (AST) — la pieza que conecta todo

Hay un concepto clave que hace posible toda la conversión:

> 👉 El **árbol lógico (AST: Abstract Syntax Tree)**

---

## 🤔 ¿Qué es un AST en este contexto?

Es una forma de representar la lógica **como una estructura jerárquica**, en lugar de una lista o un dibujo.

Por ejemplo, esta lógica:

```
(I0 AND I1) OR I2
```

Se convierte en un árbol:

```
        OR
       /  \
     AND   I2
    /   \
  I0     I1
```

---

## 🧠 ¿Por qué es tan importante?

Porque el AST permite:

* Entender correctamente prioridades (paréntesis)
* Separar lógica compleja en partes simples
* Generar código sin ambigüedades

👉 Es el paso donde la lógica deja de ser “visual” y pasa a ser “formal”.

---

## 🔗 Relación con JSON

El JSON guarda la estructura…

El AST la interpreta.

Ejemplo:

```json
{
  "type": "or",
  "left": {
    "type": "and",
    "left": {"type": "var", "name": "I0"},
    "right": {"type": "var", "name": "I1"}
  },
  "right": {"type": "var", "name": "I2"}
}
```

👉 Eso **ya es prácticamente un AST serializado**.

---

## ⚙️ ¿Cómo se usa para generar C?

El sistema recorre el árbol (recursivamente):

```python
def generar(nodo):
    if nodo.type == "var":
        return nodo.name

    if nodo.type == "and":
        return f"({generar(nodo.left)} && {generar(nodo.right)})"

    if nodo.type == "or":
        return f"({generar(nodo.left)} || {generar(nodo.right)})"
```

Resultado:

```c
Q0 = (I0 && I1) || I2;
```

---

## 💡 Idea clave para explicarlo

Si lo tenés que decir fácil:

> El JSON guarda la lógica, pero el AST es lo que realmente permite entenderla y transformarla en código.

---

## 🔄 ¿Cómo ocurre la “magia”?

En realidad no hay magia, hay un proceso:

```
Lo que dibujás (Ladder / Blocks)
                ↓
Se convierte en conexiones
                ↓
Se arma un modelo lógico (JSON)
                ↓
Se interpreta como lógica booleana
                ↓
Se genera código C
```

---

## ⚙️ ¿Y cómo se ejecuta en Arduino?

Arduino no es un PLC… pero lo hacemos comportarse como uno.

```c
void loop() {
  readInputs();
  executeLogic();
  writeOutputs();
}
```

Esto se repite constantemente.

👉 Igual que un PLC real.

---

## 🔧 Ejemplo completo

### Lo que el usuario ve

```
--[ I0 ]--[ I1 ]----( Q0 )
```

### Lo que uPLC entiende

```c
Q0 = I0 && I1;
```

### Lo que ejecuta Arduino

```c
void loop() {
  I0 = digitalRead(2);
  I1 = digitalRead(3);

  Q0 = I0 && I1;

  digitalWrite(8, Q0);
}
```

---

## 🧨 Cuando el sistema crece

Ahí es donde uPLC deja de ser “educativo” y pasa a ser potente:

* Memorias (SET / RESET)
* Variables internas
* Flancos
* Temporizadores

Todo eso también se puede representar en JSON y luego en C.

---

## 🚀 La idea central (para explicarlo en una charla)

Si lo tenés que decir en una frase:

> uPLC toma lógica visual (Ladder o Bloques), la convierte en un modelo estructurado (JSON), y a partir de eso genera código real que se ejecuta como un PLC.

---

## 🔚 Cierre

* No es un editor gráfico
* No es solo educativo
* Es un **intérprete de lógica industrial**

👉 Y eso es lo que lo hace potente.

---

Este enfoque permite enseñar desde cero…
y al mismo tiempo construir sistemas reales.
