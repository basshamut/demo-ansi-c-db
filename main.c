#include <stdio.h>
#include <stdlib.h>
#include "libpq-fe.h"

int main() {
    // Cadena de conexión (modificar con tus datos)
    const char *conninfo = "host=localhost dbname=condominio user=postgres password=1234";
    
    // Establecer conexión
    PGconn *conn = PQconnectdb(conninfo);

    // Verificar conexión
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Error de conexión: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        return 1;
    }

    printf("Conexión exitosa a PostgreSQL\n");

    // Ejecutar consulta
    PGresult *res = PQexec(conn, "SELECT version();");

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Error en consulta: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        return 1;
    }

    // Imprimir resultado
    printf("Versión de PostgreSQL: %s\n", PQgetvalue(res, 0, 0));

    // Liberar memoria
    PQclear(res);
    PQfinish(conn);
    return 0;
}
/*
gcc main.c -o main.exe -I. -L. -lpq
./main.exe
*/