# RPG Universidad - Aventura Académica

## Descripción del Juego

Un juego de rol ambientado en una universidad donde los estudiantes deben enfrentar a sus profesores en combate académico. El juego presenta 6 personajes jugables únicos, cada uno con sus propias fortalezas y debilidades.

## Personajes Jugables

### 1. Robert
- **Descripción**: Líder del equipo, balanceado en todas las áreas
- **Estadísticas**: Vida: 120, Ataque: 15, Defensa: 12, Velocidad: 10
- **Color**: Azul
- **Especialidad**: Personaje equilibrado, ideal para principiantes

### 2. Franco
- **Descripción**: Guerrero fuerte, alto ataque y defensa
- **Estadísticas**: Vida: 150, Ataque: 20, Defensa: 18, Velocidad: 6
- **Color**: Rojo
- **Especialidad**: Tank ofensivo, perfecto para jugadores agresivos

### 3. Coutencos
- **Descripción**: Estratega inteligente, ataques especiales
- **Estadísticas**: Vida: 90, Ataque: 18, Defensa: 8, Velocidad: 14
- **Color**: Púrpura
- **Especialidad**: Alto daño pero frágil, requiere estrategia

### 4. Fercha
- **Descripción**: Explorador rápido, alta velocidad
- **Estadísticas**: Vida: 100, Ataque: 12, Defensa: 10, Velocidad: 18
- **Color**: Verde
- **Especialidad**: El más rápido, ideal para hit-and-run

### 5. Aldo
- **Descripción**: Tanque defensivo, resistente al daño
- **Estadísticas**: Vida: 180, Ataque: 10, Defensa: 22, Velocidad: 4
- **Color**: Marrón
- **Especialidad**: Máxima defensa y vida, lento pero resistente

### 6. Chema
- **Descripción**: Apoyo técnico, habilidades especiales
- **Estadísticas**: Vida: 85, Ataque: 14, Defensa: 9, Velocidad: 12
- **Color**: Amarillo
- **Especialidad**: Personaje de apoyo con habilidades únicas

## Enemigos - Profesores

### Prof. Algebra (Matemáticas)
- Vida: 80, Ataque: 12, Defensa: 8
- Experiencia: 25 puntos

### Prof. Newton (Física)
- Vida: 100, Ataque: 15, Defensa: 10
- Experiencia: 30 puntos

### Prof. Code (Programación)
- Vida: 70, Ataque: 18, Defensa: 6
- Experiencia: 35 puntos

### Prof. Elemento (Química)
- Vida: 90, Ataque: 16, Defensa: 12
- Experiencia: 40 puntos

### Director (Jefe Final)
- Vida: 200, Ataque: 25, Defensa: 20
- Experiencia: 100 puntos

## Controles

- **WASD / Flechas**: Movimiento del personaje
- **ESPACIO**: Atacar en combate
- **ESC**: Huir del combate
- **R**: Reiniciar juego (en Game Over o Victoria)
- **ENTER**: Confirmar selección

## Estados del Juego

1. **Selección de Personaje**: Elige tu héroe entre los 6 disponibles
2. **Exploración**: Muévete por el mapa de la universidad
3. **Combate**: Enfréntate a los profesores en combate por turnos
4. **Victoria**: Derrota a todos los profesores para ganar

## Mecánicas del Juego

### Sistema de Experiencia
- Gana experiencia derrotando profesores
- Sube de nivel cada 100 puntos de experiencia
- Al subir de nivel aumentan todas las estadísticas

### Sistema de Combate
- Combate por turnos cuando te acercas a un profesor
- El daño se calcula: Ataque - Defensa/2 (mínimo 1)
- Los profesores tienen IA simple: patrullan, persiguen y atacan

### Balanceo de Personajes
Cada personaje tiene un total de estadísticas diferente, creando diferentes estilos de juego:
- Robert: 157 puntos (equilibrado)
- Franco: 194 puntos (tanque ofensivo)
- Coutencos: 130 puntos (glass cannon)
- Fercha: 140 puntos (velocista)
- Aldo: 216 puntos (tanque defensivo)
- Chema: 120 puntos (apoyo/técnico)

## Compilación y Ejecución

```bash
# Compilar el juego
make

# Ejecutar
./rpg
```

## Requisitos
- Raylib (para gráficos y entrada)
- GCC con soporte C99
- Librerías del sistema: OpenGL, X11, etc.

## Estructura del Código

- `src/main.c`: Bucle principal del juego
- `src/game.c/h`: Gestión de estados y lógica general
- `src/player.c/h`: Sistema de personajes jugables
- `src/enemy.c/h`: Sistema de enemigos (profesores)
- `src/map.c/h`: Sistema de mapas y renderizado

¡Disfruta derrotando a tus profesores en esta aventura académica única!