#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

void check_connection(PGconn *conn);
void execute_query(PGconn *conn, const char *query);
void insert_data(PGconn *conn, const char *name, int age);
void select_all_data(PGconn *conn);
void update_data(PGconn *conn, const char *name, int new_age);
void delete_data(PGconn *conn, const char *name);

int main()
{
    const char *conninfo = "host=localhost dbname=localtest_db user=postgres password=1234";
    PGconn *conn = PQconnectdb(conninfo);

    check_connection(conn);

    execute_query(conn, "SELECT version();");

    insert_data(conn, "Juan", 30);
    insert_data(conn, "Jose", 40);

    select_all_data(conn);

    update_data(conn, "Jose", 35);

    delete_data(conn, "Juan");

    PQfinish(conn);
    return 0;
}

void check_connection(PGconn *conn)
{
    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "Error de conexión: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }
    printf("Conexión exitosa a PostgreSQL\n");
}

void execute_query(PGconn *conn, const char *query)
{
    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Error en consulta: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }

    printf("Versión de PostgreSQL: %s\n", PQgetvalue(res, 0, 0));
    PQclear(res);
}

void insert_data(PGconn *conn, const char *name, int age)
{
    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO general.usuarios (nombre, edad) VALUES ('%s', %d);", name, age);

    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "Error al insertar: %s\n", PQerrorMessage(conn));
    }
    else
    {
        printf("Inserción exitosa\n");
    }

    PQclear(res);
}

void select_all_data(PGconn *conn)
{
    PGresult *res = PQexec(conn, "SELECT nombre, edad FROM general.usuarios;");

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Error en consulta SELECT: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    int filas = PQntuples(res);
    printf("Usuarios en la base de datos:\n");

    for (int i = 0; i < filas; i++)
    {
        printf("Nombre: %s, Edad: %s\n",
               PQgetvalue(res, i, 0), // Columna 0: nombre
               PQgetvalue(res, i, 1)  // Columna 1: edad
        );
    }

    PQclear(res);
}

void update_data(PGconn *conn, const char *name, int new_age)
{
    char query[256];
    snprintf(query, sizeof(query), "UPDATE general.usuarios SET edad = %d WHERE nombre = '%s';", new_age, name);

    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "Error al actualizar: %s\n", PQerrorMessage(conn));
    }
    else
    {
        printf("Actualización exitosa\n");
    }

    PQclear(res);
}

void delete_data(PGconn *conn, const char *name)
{
    char query[256];
    snprintf(query, sizeof(query), "DELETE FROM general.usuarios WHERE nombre = '%s';", name);

    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "Error al eliminar: %s\n", PQerrorMessage(conn));
    }
    else
    {
        printf("Eliminación exitosa\n");
    }

    PQclear(res);
}