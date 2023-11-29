section .text
global _initMatrix
global _setValue
global _isSameColor
global _getCellValue
global _getCell
global _readColRowSize
global _pointsSystem
global _withinMatrix
;global _elementsAreAdjacent
; global _eliminateElement
;global _applyGravity

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

;XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
; funcion que sirve para el control de las puntuaciones.
; parametros:
; rdi = combinationPoints
; rsi = this->currentScore

_pointsSystem:
	mov rax, rdi
	add rax, rsi
	ret

;XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
; Funcion que revisa si tamanos de cols y rows
; Parametros
; rdi rowColSize

_readColRowSize:
	cmp rdi, 8
	jl fueraDeTamano
	cmp rdi, 10
	jg fueraDeTamano
	mov rax, 1
	jmp exitRead

fueraDeTamano:
	xor rax, rax
exitRead:
	ret

;XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
; Funcion que revisa si tamanos que una posicion este dentro de la matriz
; Parametros
; rdi = row
; rsi = col
; rdx = this->rowSize
; rcx = this->colSize


_withinMatrix:
	; Revisar rows
	cmp rdi, 0
	jl fueraDeMatriz
	cmp rdi, rdx
	jge fueraDeMatriz

	; Revisar cols
	cmp rsi, 0
	jl fueraDeMatriz
	cmp rsi, rcx
	jge fueraDeMatriz
	
	; Significa que se cumple todo.
	mov rax, 1
	jmp exitWithin

fueraDeMatriz:
	xor rax, rax
	
exitWithin:
	ret

;XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
; Funcion que revisa si los elementos son adyancentes
; Parametros
; rdi rowCurrent
; rsi colCurrent
; rdx rowDestination
; rcx colDestination

;_elementsAreAdjacent:
	;mov r8, rsi
	;dec r8
	;mov r9, rsi
	;inc r9
	;mov r10, rdi
	;dec r10
	;mov r11, rdi
	;inc r11
; ya estan los valores correctos
	;cmp rdi, rdx
	;jne revisarColumnas

	; si son iguales 
	;cmp r8, rcx
	;je sonAdyacentes
	;cmp r9, rcx
	;je sonAdyacentes
	;jmp noAdyacentes

;revisarColumnas:
	;cmp rsi, rcx
	;jne noAdyacente

	; si son iguales
	;cmp r10, rdx
	;je sonAdyacentes
	;cmp r11, rdx
	;je sonAdyacentes
	;jmp noAdyacentes

;sonAdyacentes:
;	mov rax, 1
;	jmp exitAdyacentes

;noAdyacentes:
;	xor rax, rax

;exitAdyacentes:
;	ret

;XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
;funcion de ensambla para eliminar un valor especifico, retorna un booleano de si se elimino bien
  ;parametros eliminate
  ; rdi = dirección de memoria de la matriz
  ; rsi = tamaño filas (this-> rowSize)
  ; rdx = tamaño columnas (this-> colSize)
  ; rcx = row
  ; r8 = col
  _eliminateElement:	
    ;guardar parametros iniciales
    mov r10, rdi ; rdi = dirección de memoria de la matriz
    mov r11, rsi ; rsi = tamaño filas
    mov r12, rdx ; rdx = tamaño columnas
    mov r13, rcx ; rcx = row
    
    ;cambiar parametros orden
    mov rdi, r13 ; rdi = row
    mov rsi, r8 ; rsi = col
    mov rdx, r11 ; rdx = this->rowSize
    mov rcx, r12 ; rcx = this->colSize

    call _withinMatrix
    cmp rax, 0
    je error

    ;cambiar parametros orden
    mov rdi, r10 ; rdi = row
    mov rsi, r11 ; rsi = col
    mov rdx, r12 ; rdx = this->rowSize
    mov rcx, r13 ; rcx = this->colSize
    mov r9, 0 ; r9 = newValue (0 en este caso)

    call _setValue
    mov rax, 1
    ret

error:
  xor rax, rax
  ret

;XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
;funcion de ensambla para hacer la gravedad
  ;parametros eliminate
  ; rdi = dirección de memoria de la matriz
  ; rsi = tamaño filas (this-> rowSize)
  ; rdx = tamaño columnas (this-> colSize)
;_applyGravity:
	;guardar parametros iniciales
    ;mov r10, rdi ; rdi = dirección de memoria de la matriz
    ;mov r11, rsi ; rsi = tamaño filas
    ;mov r12, rdx ; rdx = tamaño columnas
	
	; primer for
	;for (int colIndex = 0; colIndex < this->colSize; colIndex++)
	;mov r15, 0		;colIndex	
;for1:
	;;mov r15, 0		;colIndex
	;cmp r15, r12	;colIndex < this->colSize
	;jge salirFor1
	; si r15 es menor que this->colSize
	;mov r8, r11 
	;dec r8			;	int destinationRow = this->rowSize - 1

	;segundo for
	;for (int rowIndex = this->rowSize - 1; rowIndex >= 0; rowIndex--) 
	;mov rbx, r11 	
	;dec rbx			; int rowIndex = this->rowSize - 1
;for2:
	;;mov rbx, r11 	
	;;dec rbx			; int rowIndex = this->rowSize - 1
	;cmp rbx, 0
	;jl salirFor2

	;;int cellValue = _getCellValue(this->gameMatrix,this->rowSize,this->colSize,rowIndex,colIndex);

	;mov rdi, r10	;this->gameMatrix
	;mov rsi, r11	;this->rowSize
	;mov rdx, r12	;this->colSize
	;mov rcx, rbx	;rowIndex
	;mov r8, r15		;colIndex
	;call _getCellValue

	;mov r14, rax	;int cellValue
	;cmp r14, 0		if (cellValue!= 0)
	;je aumentarFor2
	;_setValue(this->gameMatrix,this->rowSize,this->colSize,destinationRow,colIndex,cellValue);
	;mov rdi, r10	;this->gameMatrix
	;mov rsi, r11	;this->rowSize
	;mov rdx, r12	;this->colSize
	;mov rcx, rbx	;rowIndex
	;mov r8, r15		;colIndex
	;mov r9, r14 	;cellValue
	;call setValue

	;cmp r8, rbx 	;if (destinationRow != rowIndex)
	;je seguir
	;_setValue(this->gameMatrix,this->rowSize,this->colSize,rowIndex,colIndex,0);
	;mov rdi, r10	;this->gameMatrix
	;mov rsi, r11	;this->rowSize
	;mov rdx, r12	;this->colSize
	;mov rcx, rbx	;rowIndex
	;mov r8, r15		;colIndex
	;mov r9, 0 	;0
	;call setValue

;seguir:
	;dec r8			;destinationRow--

;aumentarFor2:
	;dec rbx 	; rowIndex--
	;jmp for2

;salirFor2:
	;inc r15		; colIndex++
	;jmp for1
	
;salirFor1
	;ret