#!/bin/bash

# Este script testea la validación de mapas para el proyecto so_long.
# Debe ser ejecutado desde la raíz del proyecto.
# Los mapas deben estar en una carpeta llamada 'maps'.

# Colores para la salida en la terminal
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Limpiar y compilar el proyecto
echo -e "${CYAN}--- Compilando so_long... ---${NC}"
make fclean > /dev/null
make > /dev/null

if [ ! -f "so_long" ]; then
    echo -e "${RED}Error: La compilación falló. Asegúrate de que tu Makefile funciona correctamente.${NC}"
    exit 1
fi

echo -e "${GREEN}Compilación exitosa.${NC}"
echo -e "${CYAN}-------------------------------------${NC}"

# Asegurarse de que el directorio de mapas existe
if [ ! -d "maps" ]; then
    echo -e "${RED}Error: No se encontró la carpeta 'maps'. Por favor, créala y coloca tus archivos .ber dentro.${NC}"
    exit 1
fi

# Contadores de resultados
TOTAL_TESTS=0
SUCCESS_COUNT=0
FAILURE_COUNT=0

# Iterar sobre todos los archivos .ber en el directorio 'maps'
for map_file in maps/*.ber; do
    if [ -f "$map_file" ]; then
        TOTAL_TESTS=$((TOTAL_TESTS + 1))
        echo -e "${YELLOW}Testeando el mapa: $map_file${NC}"

        # Ejecutar el programa con el mapa actual
        ./so_long "$map_file" > output.txt 2>&1
        exit_code=$?

        # Mostrar el resultado del test
        echo -e "${YELLOW}Salida del programa:${NC}"
        cat output.txt
        
        echo -e "${YELLOW}Código de salida (0 = éxito, >0 = error):${NC} $exit_code"
        
        # Evaluar el código de salida para una retroalimentación más clara
        if [ $exit_code -eq 0 ]; then
            echo -e "${GREEN}Resultado: PASSED (El programa terminó sin error).${NC}"
            SUCCESS_COUNT=$((SUCCESS_COUNT + 1))
        else
            echo -e "${RED}Resultado: FAILED (El programa terminó con un error).${NC}"
            FAILURE_COUNT=$((FAILURE_COUNT + 1))
        fi
        
        echo -e "${CYAN}-------------------------------------${NC}"
    fi
done

# Resumen final de los resultados
echo -e "${CYAN}--- Resumen de los tests ---${NC}"
echo -e "Total de mapas testeados: ${TOTAL_TESTS}"
echo -e "Mapas exitosos: ${GREEN}${SUCCESS_COUNT}${NC}"
echo -e "Mapas fallidos: ${RED}${FAILURE_COUNT}${NC}"

# Limpiar los archivos temporales
rm -f output.txt

echo -e "${CYAN}--- Todos los tests completados. ---${NC}"
