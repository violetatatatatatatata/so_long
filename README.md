# so_long

Este proyecto es un pequeño juego en 2D que te permite mover a un personaje a través de un mapa para recoger objetos y escapar. El objetivo es recolectar todos los objetos y salir del mapa, evitando chocar con los muros. El juego se construye utilizando la librería gráfica MiniLibX.

![til](https://c.tenor.com/HAPT5_bel_QAAAAC/tenor.gif)
### Requisitos de Compilación

Para compilar y ejecutar el proyecto, necesitas tener instalada la librería [MiniLibX](https://github.com/42paris/minilibx-linux.git) con su propia [documentación oficial](https://harm-smits.github.io/42docs/libs/minilibx)

### Guía de Referencia

Este proyecto se ha desarrollado siguiendo la guía de referencia disponible en:
[https://42-cursus.gitbook.io/guide](https://42-cursus.gitbook.io/guide)

### Cómo Jugar

1.  Asegúrate de tener un archivo `.ber` válido en la carpeta `maps`.
2.  Compila el proyecto con el comando `make`.
3.  Ejecuta el programa pasando la ruta del mapa como argumento: `./so_long maps/mapa_valido.ber`.
4.  Usa las teclas `W`, `A`, `S` y `D` para mover al personaje.
5.  El número de movimientos se mostrará en el terminal.
6.  Presiona `ESC` para salir del juego.
