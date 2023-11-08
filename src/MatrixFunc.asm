section .text
global _initMatrix
global _setValue
global _isSameColor
global _getCellValue
global _getCell

;funcion para inicializar la matriz
; Parámetros:
; rdi = dirección de memoria de la matriz
; rsi = número de filas
_initMatrix:
    ; Inicializacion de la matriz en 0
    xor rax, rax  ; Valor cero en rax

    ; Loop para inicializar la matriz
    mov rcx, rsi  ; Número de filas

;loop filas
_init_row_loop:
    mov rbx, rsi  ; Número de columnas

;loop columnas
_init_col_loop:
    mov [rdi], al  ; Almacena cero en la ubicación de la matriz
    inc rdi       ; Avanza al siguiente elemento
    dec rbx       ; Decrementa el contador de columnas
    jnz _init_col_loop  ; Repite hasta que rbx sea cero
    dec rcx       ; Decrementa el contador de filas
    jnz _init_row_loop  ; Repite hasta que rcx sea cero

    ret

;funcion que retorna la direccion de una celda
    ; Parámetros:           
    ; rdi = dirección de memoria de la matriz
    ; rsi = filas
    ; rdx = columnas
    ; rcx = fila
    ; r8 = columna
_getCell:
    ; Calcula el índice en el arreglo unidimensional
    imul rsi, rcx   ; fila * número de columnas
    add rsi, r8   ; fila * número de columnas + columna
    ; Multiplica rsi por 4 (rsi * 4)
    shl rsi, 2
    lea rax, [rdi + rsi]  ; Suma el resultado (rsi * 4) a la dirección de memoria base
    ret


;funcion que cambia el valor de una celda
    ; Parámetros:           
    ; rdi = dirección de memoria de la matriz
    ; rsi = filas
    ; rdx = columnas
    ; rcx = fila
    ; r8 = columna
    ; r9  = nuevo valor
_setValue:
    ;llama a la funcion que obtiene la direccion de la celda
    call _getCell

    ; Almacena el nuevo valor en la celda
    mov [rax], r9d
    ret


; Función que obtiene el valor de una celda en la matriz
    ; Parámetros:
    ; rdi = dirección de memoria de la matriz
    ; rsi = número de filas
    ; rdx = número de columnas
    ; rcx = fila
    ; r8 = columna
    ; Retorna:
    ; rax = valor de la celda
_getCellValue:

    ;llama a la funcion que obtiene la direccion de la celda
    call _getCell

    ; Carga el valor en la celda
    mov eax, [rax]  ; Carga el valor de 4 bytes (asumiendo que son enteros de 32 bits)

    ret

    
;Funcion que compara colores
    ; Parámetros:
    ; rdi = dirección de memoria de la matriz
    ; rsi = fila
    ; rdx = columna
    ; rcx = color
    ; r8  = tamaño de la fila (rowSize)
_isSameColor:

    imul rsi, r8        ; fila * número de columnas
    add rsi, rdx         ; fila * número de columnas + columna
    shl rsi, 2           ; Multiplica el índice por 4 para tener en cuenta el tamaño de un elemento (4 bytes)


    ; Compara el valor en la matriz con el color
    mov al, byte [rdi + rsi]  ; Carga el valor en al
    cmp al, cl                ; Compara el valor en al con el color
    je _iguales
    xor al, al                   ; Establece al en 1 si son iguales, en 0 si son diferentes

    ret
;etiqueta si los colores son iguales, devuelve un 1
_iguales:
    mov al, 1
    ret
