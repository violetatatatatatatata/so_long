# so_long

Este proyecto es un pequeño juego en 2D que te permite mover a un personaje a través de un mapa para recoger objetos y escapar. El objetivo es recolectar todos los objetos y salir del mapa, evitando chocar con los muros. El juego se construye utilizando la librería gráfica MiniLibX.

### Requisitos de Compilación

Para compilar y ejecutar el proyecto, necesitas tener instalada la librería MiniLibX.
[https://github.com/42paris/minilibx-linux.git](https://github.com/42paris/minilibx-linux.git)
Documentacion oficial: [https://harm-smits.github.io/42docs/libs/minilibx](https://harm-smits.github.io/42docs/libs/minilibx)

### Guía de Referencia

Este proyecto se ha desarrollado siguiendo la guía de referencia disponible en:
[https://42-cursus.gitbook.io/guide](https://42-cursus.gitbook.io/guide)

### Estructura de Archivos

La estructura del proyecto es la siguiente:

.
├── Makefile
├── README.md
├── maps/
│   ├── mapa_valido.ber
│   └── mapa_invalido.ber
├── srcs/
│   ├── game_logic.c
│   ├── main.c
│   ├── map.c
│   ├── render.c
│   ├── sprite_init.c
│   └── utils.c
├── textures/
│   ├── exit_closed.xpm
│   ├── exit_opened.xpm
│   ├── floor.xpm
│   ├── collectible.xpm
│   ├── player.xpm
│   └── wall.xpm
├── libft/
│   ├── Includes/
│   └── srcs/
├── minilibx-linux/
└── solong.h


### Cómo Jugar

1.  Asegúrate de tener un archivo `.ber` válido en la carpeta `maps`.
2.  Compila el proyecto con el comando `make`.
3.  Ejecuta el programa pasando la ruta del mapa como argumento: `./so_long maps/mapa_valido.ber`.
4.  Usa las teclas `W`, `A`, `S` y `D` para mover al personaje.
5.  El número de movimientos se mostrará en el terminal.
6.  Presiona `ESC` para salir del juego.
