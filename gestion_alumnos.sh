#!/bin/bash

#Sistema gestion de alumnos
#1-Preparacion del entorno
#Mostrar informacion
echo "Usuario actual: $USER"
FECHA=$(date)
echo "Fecha: $FECHA"
echo "Directorio del trabajo: $PWD"
echo "Nombre del equipo: $HOSTNAME"

#CREAR VARIABLES DE RUTAS
BASE="gestion_alumnos"
DOCUMENTOS="$BASE/documentos"
RESPALDOS="$BASE/respaldos"
REPORTES="$BASE/reportes"
LOGS="$BASE/logs"
ALUMNOS="$DOCUMENTOS/alumnos.txt"
REPORTE="$REPORTES/reporte.txt"

if [ -d "$BASE" ]; then
	echo "La carpeta gestion_alumnos si existe"
else
	mkdir "$BASE"
	echo "La carpeta gestion_alumnos fue creada"
fi

if [ -d "$DOCUMENTOS" ]; then
	echo "La carpeta documentos si existe"
else
	mkdir "$DOCUMENTOS"
	echo "La carpeta documentos fue creada"
fi

if [ -d "$RESPALDOS" ]; then
	echo "La carpeta respaldos si existe"
else
	mkdir "$RESPALDOS"
	echo "La carpeta respaldos fue creada"
fi
if [ -d "$REPORTES" ]; then
	echo "La carpeta reportes existe"
else
	mkdir "$REPORTES"
	echo "La carpeta reportes fue creada"
fi
if [ -d "$LOGS" ]; then
	echo "La carpeta logs existe"
else
	mkdir "$LOGS"
	echo "La carpeta logs fue creada"
fi
if [ -f "$ALUMNOS" ]; then
	echo "El archivo alumnos existe"
else
	touch "$ALUMNOS"
	echo "El archivo alumnos fue creado"
fi

if [ -f "$REPORTE" ]; then
	echo "El archivo reporte si existe"
else
	touch "$REPORTE"
	echo "El archivo reporte fue creado"
fi

tree


if [ "S1" = "reporte" ]; then
	generar_reporte
	exit
elif [ "$1" = "respaldo" ]; then
	realizar_respaldo
	exit
elif [ -n "$1" ]; then
	grep -i "$1" "$ALUMNOS"
	exit
fi

registrar_alumno(){
	local nombre
	local edad
	local carrera
	local calificacion
	read -p "Ingresa el nombre del alumno: " nombre
	read -p "Ingresa la edad: " edad
	read -p "Ingresa la carrera: " carrera
	read -p "Calificación final (0 a 100): " calificacion
	until [[ "$calificacion"=~^[0-9]+$ ]] && [ "$calificacion" -le 100 ]; do
		echo "Calificacion no es válida. Debe ser un numero entre 0 y 100"
		read -p "Ingresa nuevamente la calificación: " calificacion
	done
	if [ -z "$nombre" ]; then
		echo "El nombre esta vacío"
	else
		echo "Nombre y la calificación válidas"
		set -x
			echo "$nombre,$edad,$carrera,$calificacion" >> "$ALUMNOS"
		set +x
		echo "Alumno registrado"
	fi
	longitud=${#nombre}
	echo "Longitud del nombre: $longitud caracteres"
}

generar_reporte(){
	local nombre edad carrera calificacion
	local aprobados reprobados suma
	echo "======REPORTE DE ALUMNOS=====" > "$REPORTE"
	sort "$ALUMNOS" | uniq >> "$REPORTE"
	total=$(wc -l < "$ALUMNOS")
	printf "\n" >> "$REPORTE"
	echo "TOTAL DE ALUMNOS: $total" >> "$REPORTE"
	aprobados=0
	reprobados=0
	suma=0
	declare -A carreras
	carreras=()
	while IFS=, read -r nombre edad carrera calificacion; do
		if [ "$calificacion" -ge 70 ]; then
			((aprobados++))
		else
			((reprobados++))
		fi
		suma=$((suma+calificacion))
		((carreras["$carrera"]++))
	done < "$ALUMNOS"
	echo "ALUMNOS APROBADOS: $aprobados" >> "$REPORTE"
	echo "ALUMNOS REPROBADOS: $reprobados" >> "$REPORTE"
	printf "\n" >> "$REPORTE"
	echo "Alumnos por carrera" >> "$REPORTE"
	for carrera in "${!carreras[@]}"; do
		echo "$carrera: ${carreras[$carrera]}" >> "$REPORTE"
		while IFS=, read -r nombre edad carrera_alumno calificacion; do
			if [ "$carrera_alumno" = "$carrera" ]; then
				echo "Alumno: $nombre" >> "$REPORTE"
			fi
		done < "$ALUMNOS"
	done
	promedio=0
	if [ "$total" -gt 0 ]; then
		promedio=$((suma/total))
	fi
	printf "\n" >> "$REPORTE"
	echo "PROMEDIO GENERAL: $promedio" >> "$REPORTE"
	echo "REPORTE GENERADO CORRECTAMENTE"

}

buscar_alumno(){
	local nombre="$1"
	grep -i "$nombre" "$ALUMNOS"


}

realizar_respaldo(){
	RESPALDO="$RESPALDOS/alumnos_$FECHA.txt"
	if [ -f "$ALUMNOS" ]; then
		cp "$ALUMNOS" "$RESPALDO" 2>> "$LOGS/errores.txt" &&
		echo "$FECHA respaldo geenerado correctamente: $RESPALDO" >> "$LOGS/actividad.txt" &&
		echo "Respaldo generado correctamente" ||
		echo "Error al realizar el respaldo"
	else
		echo "Error: el archivo alumnos.txt no existe"
		echo "$FECHA: Error: el archivo alumnos.txt no existe" >> "$LOGS/actividad.txt"
	fi
}

mostrar_informacion(){

	echo "Usuario actual: $USER"
	echo 'Usuario actual: $USER'
	echo "Fecha: $FECHA"
	echo "Directorio del trabajo: $PWD"
	echo "Nombre del equipo: $HOSTNAME"
	echo ""
	echo "========SUBSHELL========"
	(
		cd "$RESPALDOS" || exit 1
		echo "Directorio actual $PWD"
	)
	echo "Directorio actual $PWD"
	echo ""
        echo "========AGRUPACION========"
        local contador=1
        {
                contador=2
                echo "Dentro de la agrupación: $contador"
        }
        echo "Dentro de la agrupación: $contador"

}

opcion=0
while [ $opcion -ne 8 ]
do
	echo "==========MENU=========="
	echo "1. Registrar alumno."
	echo "2. Mostrar alumnos registrados."
	echo "3. Buscar alumno."
	echo "4. Generar reporte de alumnos."
	echo "5. Mostrar estadísticas."
	echo "6. Realizar respaldo."
	echo "7. Mostrar información del sistema."
	echo "8. Salir."
	read -p "Selecciona una opcion: " opcion
	if [ $opcion -ge 1 ] && [ $opcion -le 8 ]; then
		case "$opcion" in
			1) echo "Registrar alumno"
				registrar_alumno
			;;
			2) echo "Mostrar alumnos registrados"
				cat "$ALUMNOS" | sort
			;;
			3) echo "Buscar alumno"
				read -p "Ingresa el nombre del alumno que quieres buscar: " buscar_alumno_nombre
				buscar_alumno "$buscar_alumno_nombre"
			;;
			4) echo "Generar reporte de alumnos"
				generar_reporte
			;;
			5) echo "Mostrar estadísticas"
				cat "$REPORTE"
			;;
			6) echo "Realizar respaldo"
				realizar_respaldo
			;;
			7) echo "Mostrar información del sistema"
				mostrar_informacion
			;;
			8) echo "Salir"
			;;
		esac
	else
		echo "Opción no válida"
	fi
	printf "\n"
done








