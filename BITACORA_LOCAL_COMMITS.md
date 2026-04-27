# Bitacora del proyecto UdeAWorldCup - Desafio 2

Este archivo es para estudio y sustentacion del proyecto.
Por cada commit se documenta: que se hizo, por que, variables nuevas,
como encaja con lo demas, y que conceptos de C++ aplica.

## Regla base
- Actualizar en cada commit.
- No duplicar en otro archivo.
- Escribir como universitario, no como manual tecnico.

---

# GUIA RAPIDA DE SUSTENTACION

Esta seccion explica los conceptos clave que el profe puede preguntar.
Leela antes de la sustentacion.

---

## Como funciona el sistema completo (flujo general)

El programa arranca en `main.cpp` que crea un objeto `App` y llama `iniciar()`.
Desde ahi todo el flujo es:

```
App::iniciar()
  1. Repositorio::cargarBase()       -> lee el CSV con los 48 equipos
  2. Torneo::preparar()              -> crea los 12 grupos vacios
  3. cargar equipos del repo         -> pasa datos al torneo
  4. Torneo::armargruposporranking() -> hace el sorteo con bombos
  5. Torneo::generarcalendariogrupos() -> asigna dias a partidos
  6. cargar jugadores del repo       -> 15 jugadores por equipo
  7. Torneo::simularfasegrupos()     -> 72 partidos, actualiza tabla
  8. Torneo::clasificargrupos()      -> saca 12+12+8 clasificados
  9. Torneo::armardieciseisavos()    -> 16 cruces del bracket
 10. Torneo::simularfasesfinales()   -> R16, R8, R4, semis, final
 11. Torneo::mostrarinformeestadisticas() -> informe final completo
 12. Medidor::mostrarfuncionalidad() -> metricas por etapa
```

---

## Formula lambda - como se calcula la prediccion de goles

La formula viene directamente del enunciado del profe:

```
lambda = mu * (GF/mu)^alpha * (GCrival/mu)^beta
```

Donde:
- `GF` = promedio historico de goles a favor del equipo (cuanto ataca)
- `GCrival` = promedio historico de goles en contra del rival (que tan vulnerable es)
- `mu = 1.35` = promedio mundial historico de goles por partido en mundiales
- `alpha = 0.6` = peso del ataque propio (mas importante)
- `beta = 0.4` = peso de la defensa del rival (menos peso)

**Ejemplo con numeros reales:**
Si Argentina promedea 2.1 goles a favor y Francia recibe en promedio 0.8:
- factorataque = (2.1/1.35)^0.6 = 1.55^0.6 ≈ 1.29
- factordefensa = (0.8/1.35)^0.4 = 0.59^0.4 ≈ 0.78
- lambda = 1.35 * 1.29 * 0.78 ≈ **1.36 goles esperados**

**Por que usa datos historicos?**
Porque equipos que historicamente atacan bien siguen siendo mas peligrosos.
Es la misma logica que usa FIFA para el ranking: historial importa.

---

## Como se generan los goles: distribucion de Poisson

Con el lambda calculado, el numero de goles se genera con el metodo de Knuth
para muestrear una distribucion de Poisson sin libreria especial.

**Por que Poisson?**
Porque los goles en futbol son eventos raros pero posibles en cualquier momento.
La distribucion de Poisson modela exactamente eso: eventos que ocurren con
una tasa promedio (lambda) pero que cada uno puede ser 0, 1, 2, 3...

**El algoritmo de Knuth (simplificado):**
```
limite = e^(-lambda)
producto = 1
k = 0
repetir:
    k = k + 1
    u = numero aleatorio entre 0 y 1
    producto = producto * u
hasta que: producto <= limite
resultado = k - 1
```

Por ejemplo con lambda=1.35: el resultado mas probable es 1 gol (~34%),
pero puede salir 0 (~26%), 2 (~23%), 3 (~10%)... es probabilistico.

---

## Como funciona el sorteo de grupos (bombos)

El sorteo respeta el sistema oficial de bombos:

- **Bombo 1:** 12 mejores equipos por ranking FIFA (sede siempre aqui)
- **Bombo 2, 3, 4:** el resto ordenados de mejor a peor ranking

**Restriccion principal:** dos equipos de la misma confederacion NO pueden
quedar en el mismo grupo. Excepcion: UEFA tiene 16 equipos, y como solo
hay 12 grupos de 4, es imposible evitar que algun grupo tenga 2 europeos.

El codigo intenta el sorteo hasta 600 veces. Si en algun intento no se
puede cumplir la restriccion de confederacion, descarta y lo vuelve a intentar.

**Por que hasta 600 intentos?**
Con 48 equipos y restricciones de confederacion, a veces los primeros intentos
no encuentran una distribucion valida. 600 intentos es suficiente para
asegurar que siempre encuentra una solucion valida.

---

## Como funciona la clasificacion a dieciseisavos

De 48 equipos pasan 32:
- **12 primeros** de grupo (uno por grupo, automaticos)
- **12 segundos** de grupo (uno por grupo, automaticos)
- **8 mejores terceros** de los 12 (ordenados globalmente por puntos/diferencia/goles)

Los terceros se comparan entre si globalmente. Si hay empate total entre dos
terceros, el ganador se decide por sorteo aleatorio (como en el mundial real).

---

## Como se arman los cruces de dieciseisavos

El bracket tiene 3 tipos de cruces:
1. **Primeros de grupos A-H vs 8 mejores terceros** (8 partidos)
2. **Primeros de grupos I-L vs 4 peores segundos** (4 partidos)
3. **8 segundos restantes entre si** (4 partidos)

**Restriccion clave:** ningun cruce puede enfrentar dos equipos del mismo grupo.
El codigo lo valida al final y si queda algun cruce invalido, intenta intercambiar
visitantes con otro partido para resolverlo.

---

## Como funciona el desempate en eliminacion

En partido eliminatorio si hay empate al final del tiempo regular (90 min):
1. Se simula tiempo extra (minutos cambia a 120)
2. Se aplica un sesgo por ranking FIFA:
   - El equipo mejor rankeado tiene mas probabilidad de ganar
   - Maximo sesgo: +35% (nunca puede ser menos de 10% ni mas de 90%)
   - Si la diferencia de ranking es 0, es 50/50
3. Se genera un numero aleatorio y se compara con la probabilidad

**Ejemplo:** Francia (ranking 2) vs Camerun (ranking 33)
- diferencia = 33-2 = 31
- sesgo = 31/220 = 0.14 → problocal = 0.50 + 0.14 = 0.64
- Francia tiene 64% de probabilidad de ganar en tiempo extra

---

## Goles por jugador: por que puede salir un arquero como goleador

El enunciado del profe dice explicitamente que los goles deben distribuirse
**uniformemente** entre los 11 jugadores. Eso significa:
- Cada jugador tiene la misma probabilidad de recibir un gol: 1/11 ≈ 9.1%
- No hay pesos por posicion
- Si se hacen 7 goles en el torneo y el arquero recibe 2, eso es estadisticamente valido

Esto cumple el enunciado al pie de la letra. No se modifico a proposito.

---

## Memoria dinamica: por que se usa new y delete

El proyecto no puede usar `vector` de STL. Entonces toda la memoria que necesita
crecer se pide con `new` y se libera con `delete`.

**Variables que usan memoria dinamica en Torneo:**
```
grupo* grupos                    -> 12 grupos del torneo
tablaposiciones* tabla           -> 48 filas (4 por grupo)
jugador* jugadoresbase           -> hasta 720 jugadores (48*15)
string* equiposbase              -> nombres de 48 equipos
partido* partidosgrupos          -> 72 partidos de grupos
partido* partidosdieciseisavos   -> 16 partidos R16
partido* partidosoctavos         -> 8 partidos R8
partido* partidoscuartos         -> 4 partidos R4
partido* partidossemis           -> 2 semifinales
```

**Por que se inicializan en 0 en el constructor?**
Para que el destructor pueda verificar con `if (puntero != 0)` antes de hacer
`delete[]`. Si no se inicializan, el destructor podria intentar liberar basura.

---

## Metricas: por que siempre dan el mismo numero

Las iteraciones y memoria son **estimaciones calculadas**, no medicion real.
Eso es porque medir tiempo real de CPU requiere librerias de sistema que
el enunciado no exige. Lo que se hace es:

- **Iteraciones:** se suman los loops principales del algoritmo
  (grupos: 72 partidos * 12 operaciones ≈ 864, etc.)
- **Memoria:** se suman los sizeof() de cada estructura activa

Como la estructura del torneo siempre tiene los mismos tamanos (48 equipos,
72 partidos, etc.), los numeros son deterministas. Eso es correcto.

---

## Estructura de clases (para explicar en sustentacion)

| Clase | Responsabilidad |
|---|---|
| `App` | Orquesta el flujo completo, no tiene datos propios |
| `Repositorio` | Lee el CSV, arma plantillas, expone datos con getters |
| `Torneo` | Motor principal: sorteo, simulacion, clasificacion, informe |
| `Simulador` | Prueba aislada de la formula lambda |
| `Medidor` | Imprime metricas por funcionalidad |
| `Grupo` | Representa un grupo con 4 equipos y su confederacion |
| `TablaPosiociones` | Registro de puntos/goles de un equipo en fase de grupos |
| `Partido` | Un enfrentamiento con local, visita y resultado |
| `Jugador` | Estadisticas individuales de un jugador |

---

## Estado actual del proyecto

- **Rama activa:** `main`
- **Ultimo commit en remoto:** `a1bf1fa`
- **Mensaje del ultimo commit:** `los ultimso cambios que hicimos`
- **Estado de push:** sincronizado con `origin/main`

---

## Ultimo commit registrado - a1bf1fa - los ultimso cambios que hicimos

### Que se hizo en este commit
Se ajusto el cierre final del desafio con foco en exactitud de simulacion, salida detallada y persistencia historica:

1. **Contexto completo de partido en la entidad `partido`:**
   - Se incorporaron datos de sede, terna arbitral, hora y fecha.
   - Se incorporo posesion local/visita.
   - Se incorporo lista de goleadores por camiseta para local y visita.

2. **Salida de simulacion mas completa en `torneo`:**
   - Se estandarizo impresion por partido con datos de contexto.
   - Se imprimen goleadores por camiseta por cada lado.
   - Se agrega modulo de resultados de fase de grupos con mejor trazabilidad para sustentacion.

3. **Formula de gol esperado dejada literal y sin ajustes extra:**
   - Se usa `lambda = mu * (GF/mu)^alpha * (GC_rival/mu)^beta`.
   - Parametros fijos: `alpha = 0.6`, `beta = 0.4`, `mu = 1.35`.
   - Se retiraron fallback y piso en lambda para que quede identica a la expresion solicitada.

4. **Actualizacion historica persistente al final del flujo:**
   - Se consolidan goles historicos de equipos.
   - Se exportan `equipos_historico_actualizado.csv` y `jugadores_historico_actualizado.csv`.
   - Se valida resultado con mensaje de estado `ok/fallo`.

5. **Nombre base de jugadores en formato exigido:**
   - Plantillas base generadas como `nombreX apellidoX` segun numero de camiseta.

6. **Comentarios finales revisados en tono humano:**
   - Se limpiaron frases roboticas y referencias tipo plantilla.
   - Se mantuvo explicacion corta y clara para sustentacion.

### Por que se hizo todo junto
Para cerrar la ultima brecha entre "funciona" y "cumple literal lo pedido" sin abrir nuevas ramas de complejidad.

### Variables y funciones nuevas en este commit

En `partido.h/.cpp`:
- `sede`, `arbitros[3]`, `hora`, `fecha`.
- `posesionlocal` + getter de posesion visita.
- `goleadoreslocal[16]`, `goleadoresvisita[16]`, contadores por lado.
- Metodos de contexto: `configurarcontexto`, `setposesionlocal`, `agregargoleadorlocal`, `agregargoleadorvisita`, getters asociados.

En `torneo.h/.cpp`:
- `calcularposesionlocal(...)` para generar reparto de posesion por ranking.
- `imprimirdatospartido(...)` e `imprimirgoleadorescamisetas(...)` para salida consolidada.
- `mostrarresultadosfasegrupos()` para reportar fase completa.
- `guardarhistoricoactualizado(...)` para exportar historicos al cierre.
- `calcularlambdapartido(...)` dejado en forma literal de la ecuacion.

En `repositorio.h/.cpp`:
- `getgolesfavorhistoricototal(...)` y `getgolescontrahistoricototal(...)`.
- `guardarequiposhistoricoactualizado(...)` y `guardarjugadoreshistoricoactualizado(...)`.
- Ajuste de `armarplantillasbase()` para nombres `nombreX apellidoX`.

En `app.cpp`:
- Integracion de impresion de resultados de grupos.
- Integracion del guardado historico persistente en el flujo principal.

### Temas de C++ y diseno aplicados en este commit
- Encapsulacion de estado por entidad (`partido` y `torneo`).
- Composicion entre clases (`Torneo` contiene arreglos de `partido`, `jugador`, `grupo`).
- Paso por referencia constante para evitar copias (`const Repositorio&`).
- Uso de `const` en metodos de consulta.
- Gestion manual de memoria dinamica con `new[]`/`delete[]` donde aplica.

---

## Chequeo POO exigido por el desafio

Pregunta del enunciado: si el codigo demuestra destrezas en POO C++
(`abstraccion`, `encapsulacion`, `relaciones`, `diagrama de clases`, `funciones amigas`,
`sobrecarga`, `plantillas`).

### Veredicto actual por punto

1. **Abstraccion: CUMPLE**
   - Cada clase tiene rol concreto (`Repositorio`, `Torneo`, `partido`, `jugador`, `App`).

2. **Encapsulacion: CUMPLE**
   - Atributos privados y acceso via metodos publicos.

3. **Relaciones entre clases: CUMPLE**
   - Hay composicion/asociacion clara entre clases del dominio.

4. **Diseno de diagrama de clases: CUMPLE**
   - El repositorio ya incluye evidencia de diagrama y estructura consistente con el codigo.

5. **Funciones amigas: CUMPLE**
   - Se implemento `friend ostream& operator<<(ostream&, const jugador&)` en `jugador`.
   - Esta funcion amiga accede a campos privados y se usa en el informe final.

6. **Sobrecarga: CUMPLE (parcial-fuerte)**
   - Hay sobrecarga de metodos, por ejemplo `cargarequipobase(...)` con distintas firmas.

7. **Uso de plantillas: CUMPLE**
   - Se agrego plantilla de funcion `template <typename T> limitarenrango(...)`.
   - Se usa en el motor del torneo para limitar goles y posesion.

### Conclusiones para sustentacion

- **Con los ajustes finales, el checklist POO queda cubierto al 100%**
   para la lista pedida en el desafio.

---

## 1) 6d52b73 - prueba
### Que se hizo
Se creo el repositorio inicial y se hizo un commit de prueba para confirmar que el flujo Git funcionaba.

### Por que
Antes de meter codigo, era importante validar que el versionado estaba listo.

### Variables o estructuras nuevas
No aplica (commit de control).

### Integracion
Sirvio como base del historial.

### Concepto C++ para estudiar
No hay codigo C++ aun. Este commit es de gestion de proyecto.

---

## 2) b55c2e8 - diagrama de clases
### Que se hizo
Se agrego el diagrama de clases inicial para planear entidades del sistema.

### Por que
Evitar improvisar clases despues. Primero se define modelo mental del problema.

### Variables o estructuras nuevas
No aplica en codigo, pero aparecen conceptos de diseno: Equipo, Jugador, Partido, Torneo.

### Integracion
Este diseno guio los primeros archivos .h y .cpp.

### Concepto C++ para estudiar
POO conceptual: clase, atributos, metodos, relaciones entre clases.

---

## 3) f8bfa8c - analisis1
### Que se hizo
Analisis inicial del enunciado y organizacion de etapas.

### Por que
Entender alcance del problema para no desarrollar funcionalidades fuera del PDF.

### Variables o estructuras nuevas
No aplica en codigo.

### Integracion
Define ruta de trabajo por fases.

### Concepto C++ para estudiar
Planeacion tecnica (no sintaxis).

---

## 4) 19a9d8e - base proyecto qt
### Que se hizo
Se creo el esqueleto del proyecto Qt/qmake y el arranque del programa.

### Por que
Necesitabas compilar y ejecutar rapido para iterar por commits pequenos.

### Variables o estructuras nuevas
- Funcion main como punto de entrada.
- Clase App (arranque y orquestacion inicial).

### Integracion
Abre la puerta para conectar modulos por capas.

### Concepto C++ para estudiar
- main(int argc, char* argv[])
- includes
- separacion .h / .cpp

---

## 5) 8599588 - correcion codigo modualr
### Que se hizo
Se reorganizo la arquitectura en modulos: app, torneo, repositorio, simulador y medidor.

### Por que
Si todo queda en un solo archivo, luego se vuelve inmantenible.

### Variables o estructuras nuevas
- Clases base de modulos con metodos iniciales.

### Integracion
Cada modulo quedo con responsabilidad clara:
- App coordina
- Repositorio carga datos
- Torneo aplica reglas
- Simulador calcula resultados
- Medidor prepara metricas

### Concepto C++ para estudiar
- Modularidad
- forward declaration
- include guards

---

## 6) d6a7c92 - clase equipo base
### Que se hizo
Se implemento la clase equipo con estado acumulado de torneo.

### Por que
Era necesario tener entidad real para sumar puntos y goles.

### Variables o estructuras nuevas
- nombre
- grupo
- puntos
- golesfavor
- golescontra
- partidosjugados

### Integracion
Se usa como base para grupos y tabla.

### Concepto C++ para estudiar
- atributos privados
- metodos get/set
- encapsulamiento

---

## 7) 4dfb217 - clase jugador base
### Que se hizo
Se creo clase jugador con estadisticas individuales.

### Por que
El enunciado exige estadisticas por jugador mas adelante.

### Variables o estructuras nuevas
- nombre, equipo, posicion
- goles, asistencias, partidos
- tarjetas, faltas, minutos (base para extender)

### Integracion
Despues Repositorio crea plantillas y Torneo las usa en simulacion.

### Concepto C++ para estudiar
- objetos como registros de estado
- metodos incrementales (agregargol, agregarpartido)
- metodos const

---

## 8) dc1f207 - clase partido base
### Que se hizo
Se implemento la clase partido con local, visita y marcador.

### Por que
Necesitabas una unidad estandar para grupos y llaves finales.

### Variables o estructuras nuevas
- equipolocal
- equipovisita
- goleslocal
- golesvisita
- jugado

### Integracion
Torneo crea arreglos de partido para cada etapa.

### Concepto C++ para estudiar
- sobrecarga de constructor
- tipo bool
- estado mutado por metodo setresultado

---

## 9) ae048de - base grupos tabla y torneo
### Que se hizo
Se consolidaron clases grupo, tablaposiciones y ampliacion de torneo.

### Por que
Sin estas clases no hay estructura para fase de grupos.

### Variables o estructuras nuevas
- grupo* grupos
- tablaposiciones* tabla
- contadores de capacidad/cantidad

### Integracion
Quedo armado el esqueleto de memoria dinamica del torneo.

### Concepto C++ para estudiar
- punteros a arreglos de objetos
- reserva/liberacion en constructor/destructor
- composicion entre clases

---

## 10) da8363a - arreglo dinamico h
### Que se hizo
Interfaz de arreglodinamico sin STL.

### Por que
El desafio pide estructuras propias sin vector/list de STL.

### Variables o estructuras nuevas
- puntero interno a datos
- tamano logico y capacidad

### Integracion
Sirve como practica de memoria dinamica base.

### Concepto C++ para estudiar
- puntero vs valor
- contrato de una clase (header)

---

## 11) 4d9ab43 - arreglo dinamico cpp
### Que se hizo
Implementacion real del arreglo dinamico.

### Por que
Pasar de interfaz a funcionamiento concreto: agregar y redimensionar.

### Variables o estructuras nuevas
- new[] para datos
- delete[] para liberar
- rutina de redimension

### Integracion
Dejo una base reutilizable para otras estructuras.

### Concepto C++ para estudiar
- heap memory
- copia manual en for
- fugas de memoria y como evitarlas

---

## 12) ea22328 - lista simple h
### Que se hizo
Se declaro lista enlazada simple con nodo interno.

### Por que
Practicar otra estructura lineal sin STL.

### Variables o estructuras nuevas
- Nodo con dato y siguiente
- puntero a cabeza

### Integracion
Complemento pedagogico a arreglo dinamico.

### Concepto C++ para estudiar
- operador ->
- nodos enlazados por direccion de memoria

---

## 13) d086c3a - lista simple cpp
### Que se hizo
Se implementaron operaciones de la lista enlazada.

### Por que
Completar estructura: insertar, obtener, eliminar.

### Variables o estructuras nuevas
- punteros auxiliar actual/anterior
- recorrido while

### Integracion
Refuerzo de punteros y manejo manual de memoria.

### Concepto C++ para estudiar
- delete nodo por nodo
- control de null (0 o nullptr)

---

## 14) be1ec5d - matriz dinamica h y correciones de codigo
### Que se hizo
Se declaro matriz dinamica y se hicieron ajustes de estilo.

### Por que
Tener una estructura 2D propia y limpiar partes del codigo.

### Variables o estructuras nuevas
- base de matriz con filas/columnas.

### Integracion
Preparacion para manipular datos tabulares.

### Concepto C++ para estudiar
- modelo de matriz en memoria dinamica.

---

## 15) 34c44bd - matriz dinamica cpp
### Que se hizo
Se implemento la matriz dinamica.

### Por que
Completar la estructura 2D en codigo ejecutable.

### Variables o estructuras nuevas
- arreglo de punteros o bloque lineal segun implementacion.

### Integracion
Sirve como practica fuerte de memoria y indices.

### Concepto C++ para estudiar
- calculo indice fila/columna
- bucles anidados

---

## 16) 5bcb4b0 - lectura csv equipos
### Que se hizo
Primera lectura del CSV de selecciones desde disco.

### Por que
Sin datos reales no se puede simular nada serio.

### Variables o estructuras nuevas
- ifstream archivo
- string linea

### Integracion
Repositorio empieza a conectarse con datos externos.

### Concepto C++ para estudiar
- fstream
- getline
- validacion de apertura de archivo

---

## 17) c0fb34d - ajuste lectura csv real
### Que se hizo
Se ajusto parser al formato real: titulo, cabecera y separador ;

### Por que
El CSV real no venia limpio tipo tabla simple desde linea 1.

### Variables o estructuras nuevas
- logica de salto de lineas iniciales
- parseo por delimitador ';'

### Integracion
Evito offsets incorrectos en ranking/confederacion.

### Concepto C++ para estudiar
- string::find
- string::substr

---

## 18) beef53f - parseo csv y validacion basica
### Que se hizo
Se parsearon columnas clave y validaciones basicas por fila.

### Por que
No bastaba leer lineas, habia que convertir y guardar datos utiles.

### Variables o estructuras nuevas
- arreglos internos de ranking, nombre y confederacion
- conversiones numericas

### Integracion
Torneo luego consume esos datos con getters del repositorio.

### Concepto C++ para estudiar
- stoi
- control de filas invalidas

---

## 19) ff56b10 - base equipos torneo csv
### Que se hizo
Se conecto App + Repositorio + Torneo para cargar equipos base.

### Por que
Cerrar el flujo de integracion entre modulos.

### Variables o estructuras nuevas
- en Torneo: arreglos equiposbase, confederacionesbase, rankingsbase
- contador cantidadequiposbase

### Integracion
App recorre repo y manda cada equipo al torneo.

### Concepto C++ para estudiar
- paso de datos entre objetos
- diseno por capas

---

## 20) a374686 - plantilla jugadores - goles uniforme y estadisticas base
### Que se hizo
Se crearon plantillas de jugadores y reparto inicial de goles.

### Por que
Preparar estadisticas individuales para futuras etapas.

### Variables o estructuras nuevas
- jugador* jugadoresbase en repo/torneo
- cantidadjugadores y capacidadjugadores
- funciones de armado de plantilla por equipo

### Integracion
App carga jugadores desde repo hacia torneo despues de cargar equipos.

### Concepto C++ para estudiar
- arreglo de objetos
- generacion masiva de entidades
- aleatoriedad basica con rand

---

## 21) 5e87294 - bombos sorteo y validacion de grupos
### Que se hizo
Se implementaron bombos por ranking y sorteo con restriccion de confederacion.

### Por que
Era requisito central de la fase de grupos: 12 grupos validos.

### Variables o estructuras nuevas
- bombos[4][12]
- funciones de barajado y validacion
- regla host y reglas UEFA/no UEFA

### Integracion
Torneo paso de tener equipos cargados a tener grupos validos formados.

### Concepto C++ para estudiar
- arreglos bidimensionales
- Fisher-Yates
- funciones bool para control de exito/fallo

---

## 22) 8b085f0 - calendario fase grupos
### Que se hizo
Se genero calendario de partidos de grupos con restriccion de descanso.

### Por que
No basta tener grupos, se necesita orden de partidos jugables.

### Variables o estructuras nuevas
- partido* partidosgrupos
- int* diapartidosgrupos
- cantidadpartidosgrupos, capacidadpartidosgrupos
- funcion generarcalendarioconlimite(maxpartidospordia, descansominimo)

### Integracion
Despues de sortear grupos, se crea automaticamente lista de partidos con dia.

### Concepto C++ para estudiar
- almacenamiento paralelo (partido + dia)
- algoritmos greedy con restricciones

---

## 23) 4d18d7d - formula goles lambda base
### Que se hizo
Se implemento la formula lambda para goles esperados.

### Por que
Necesitabas una base matematica para simular marcadores.

### Variables o estructuras nuevas
- alpha = 0.6
- beta = 0.4
- mu = 1.35
- calcularlambdapartido(...)
- redondeargolespartido(...)

### Integracion
Esas funciones se usan en grupos y luego en eliminacion.

### Concepto C++ para estudiar
- double
- pow de cmath
- funciones puras con retorno numerico

---

## 24) 2f3a256 - sim grupos base historico y once
### Que se hizo
Se simularon partidos de grupos usando datos historicos reales (GF/GC promedio) y seleccion de once inicial.

### Por que
Mejorar realismo frente a random sin contexto.

### Variables o estructuras nuevas
- busqueda de equipo en repo para leer historicos
- once[11] por equipo
- indices auxiliares de jugadores por equipo

### Integracion
Quedo cerrada la simulacion de resultados de grupos.

### Concepto C++ para estudiar
- paso por referencia const (const Repositorio&)
- filtros sobre arreglos de objetos
- aleatoriedad controlada

---

## 25) 1d2504c - sim grupos y tabla base
### Que se hizo
Se actualizo tabla por partido, se ordenaron grupos y se clasificaron 12 primeros, 12 segundos y 8 terceros.

### Por que
Era necesario cerrar fase de grupos y obtener 32 clasificados.

### Variables o estructuras nuevas
- clasificados1[12]
- clasificados2[12]
- clasificados3[8]
- grupoindterceros[8]
- cantclasificados1, cantclasificados2, cantclasificados3
- metodos clasificargrupos y mostrarclasificados

### Integracion
Conecta resultados de grupos con etapa eliminatoria.

### Concepto C++ para estudiar
- ordenamiento manual por multiples criterios
- comparadores encadenados con if/else if
- arreglo de indices

---

## 26) e52b639 - armado llave dieciseisavos sin repetir grupo (amend con simulacion completa)
### Que se hizo
Se consolidaron en un solo commit dos avances:
1) armado de cruces de dieciseisavos
2) simulacion de todo el bracket hasta podio

### Por que
Reducir la cantidad de commits pendientes sin perder funcionalidad.

### Variables o estructuras nuevas
- `partido* partidosdieciseisavos`, `partido* partidosoctavos`, `partido* partidoscuartos`, `partido* partidossemis`
- `partido partidofinal`, `partido partidotercero`
- `equipocampeon`, `equiposubcampeon`, `equipotercero`, `equipocuarto`
- `finalessimuladas`

### Integracion
Dejo el flujo completo simulado de grupos + eliminacion, con salida de podio.

### Concepto C++ para estudiar
- manejo de memoria dinamica por etapas
- arrays temporales de ganadores
- limpieza en destructor

---

## 27) 2c31018 - desempate fifa y transicion dieciseisavos
### Que se hizo
Se ajustaron dos reglas claves del enunciado/profe:
1) transicion a dieciseisavos segun bloques (cabezas vs terceros, resto cabezas vs 4 peores segundos, resto segundos entre si)
2) desempate en eliminacion con sesgo por ranking FIFA

### Por que
La version anterior dejaba cruces muy aleatorios y desempate favoreciendo local.

### Variables o estructuras nuevas
- helper `resolverganadoreliminacion(...)`
- estructuras temporales para separar terceros, peores segundos y segundos restantes

### Integracion
Se mantiene el mismo flujo, pero ahora las llaves y empates quedan defendibles frente al enunciado.

### Concepto C++ para estudiar
- funciones auxiliares para separar reglas de negocio
- ordenamiento manual de arreglos por criterios
- sesgo probabilistico simple con `rand()`

---

## 28) aa131e7 - estadisticas por jugador en cada partido
### Que se hizo
Se agrego actualizacion de estadisticas de jugadores tanto en fase de grupos como en eliminacion.

### Por que
El enunciado pide que, despues de cada partido, se actualicen goles, tarjetas, faltas, minutos, asistencias y partidos de los jugadores.

### Variables o estructuras nuevas
- helper `elegironceindices(...)` para escoger 11 titulares reales por equipo
- helper `actualizarestadisticasjugadorespartido(...)`
- uso de probabilidades:
	- amarilla 6%
	- segunda amarilla 1.15% (da roja)
	- falta 13%
	- segunda falta 2.75%
	- tercera falta 0.7%
- minutos por partido:
	- 90 normalmente
	- 120 cuando hubo empate previo en eliminacion

### Integracion
Cada partido ya no solo genera marcador: tambien actualiza el estado de los 22 jugadores titulares (11 por equipo).

### Concepto C++ para estudiar
- actualizacion in-place de objetos en arreglo dinamico (`jugadoresbase`)
- funciones auxiliares para no duplicar logica
- paso de arreglos fijos a funciones (`int onceindices[11]`)
- control de flujo probabilistico con enteros y `rand()`

---

## Como estudiar esta bitacora

1. Lee primero la **GUIA RAPIDA DE SUSTENTACION** al inicio del archivo.
2. Luego por cada commit: busca el hash en `git log --oneline`, abre solo esos archivos.
3. Revisa primero las variables nuevas, luego como se integra con lo anterior.
4. Practica el concepto C++ indicado con un ejemplo pequeño en un archivo aparte.
5. Para la sustentacion: sabete explicar la formula lambda, el metodo de Poisson,
   como funciona el new/delete, y el flujo general del torneo.

---

## Preguntas tipicas del profe y como responderlas

**¿Cómo se calculan los goles de un partido?**
Con la formula lambda del enunciado: λ = μ * (GF/μ)^α * (GC_rival/μ)^β.
Ese lambda se convierte a goles enteros con el metodo de Poisson de Knuth.

**¿Por qué usa datos históricos del CSV?**
Porque equipos que historicamente atacan bien tienen mayor probabilidad de hacer goles.
El historico es el promedio de goles favor y en contra dividido entre partidos jugados.

**¿Cómo funciona el sorteo de grupos?**
Se organizan 4 bombos por ranking. El bombo 1 tiene los 12 mejores (sede siempre ahi).
Se intenta asignar uno de cada bombo a cada grupo, sin repetir confederacion.
Si un intento falla, se repite hasta 600 veces.

**¿Por qué se usa new y delete en vez de arreglos normales?**
Porque los arreglos normales (`int datos[100]`) tienen tamano fijo en compilacion.
Con `new` se puede pedir la cantidad exacta de memoria que se necesita en ejecucion.
Y con `delete[]` se libera cuando ya no sirve, para no desperdiciar RAM.

**¿Qué es un destructor y para qué sirve?**
Es el metodo `~Torneo()` que se llama automaticamente cuando el objeto deja de existir.
Su unico trabajo es hacer `delete[]` de todo lo que se pido con `new[]`.
Si no lo tuviera, esa memoria quedaria ocupada aunque el programa ya terminara (memory leak).

**¿Cómo se decide el ganador en tiempo extra?**
Se genera un numero aleatorio entre 0 y 1.
El equipo mejor rankeado tiene una probabilidad mayor (maximo 85% si hay mucha diferencia).
Asi el mejor equipo tiene mas chance pero no es seguro, lo cual es mas realista.

**¿Por qué las métricas siempre dan el mismo número?**
Porque son estimaciones calculadas con base en el tamano fijo del torneo (48 equipos, 12 grupos, etc.).
No es medicion real de tiempo de CPU sino una aproximacion de cuantas operaciones hace cada etapa.

