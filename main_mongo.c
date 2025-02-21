#include <mongoc/mongoc.h>
#include <bson/bson.h>
#include <stdio.h>
#include <stdlib.h>

void insertar_usuario(mongoc_collection_t *collection) {
    bson_t *doc = BCON_NEW("nombre", BCON_UTF8("Juan"), "edad", BCON_INT32(30));
    bson_error_t error;

    if (!mongoc_collection_insert_one(collection, doc, NULL, NULL, &error)) {
        fprintf(stderr, "Error al insertar: %s\n", error.message);
    } else {
        printf("Usuario insertado correctamente\n");
    }

    bson_destroy(doc);
}

void leer_usuarios(mongoc_collection_t *collection) {
    mongoc_cursor_t *cursor;
    const bson_t *doc;
    bson_t *query = bson_new();
    
    cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);

    printf("Usuarios en la base de datos:\n");
    while (mongoc_cursor_next(cursor, &doc)) {
        char *json = bson_as_canonical_extended_json(doc, NULL);
        printf("%s\n", json);
        bson_free(json);
    }

    bson_destroy(query);
    mongoc_cursor_destroy(cursor);
}

void actualizar_usuario(mongoc_collection_t *collection) {
    bson_t *query = BCON_NEW("nombre", BCON_UTF8("Juan"));
    bson_t *update = BCON_NEW("$set", "{", "edad", BCON_INT32(35), "}");

    bson_error_t error;
    if (!mongoc_collection_update_one(collection, query, update, NULL, NULL, &error)) {
        fprintf(stderr, "Error al actualizar: %s\n", error.message);
    } else {
        printf("Usuario actualizado correctamente\n");
    }

    bson_destroy(query);
    bson_destroy(update);
}

void eliminar_usuario(mongoc_collection_t *collection) {
    bson_t *query = BCON_NEW("nombre", BCON_UTF8("Juan"));

    bson_error_t error;
    if (!mongoc_collection_delete_one(collection, query, NULL, NULL, &error)) {
        fprintf(stderr, "Error al eliminar: %s\n", error.message);
    } else {
        printf("Usuario eliminado correctamente\n");
    }

    bson_destroy(query);
}

int main() {
    mongoc_client_t *client;
    mongoc_collection_t *collection;

    // Inicializar MongoDB
    mongoc_init();

    // Conectar a la base de datos MongoDB
    client = mongoc_client_new("mongodb://mongo:1234@localhost:27017");
    if (!client) {
        fprintf(stderr, "Error al conectar a MongoDB\n");
        return 1;
    }

    // Seleccionar la base de datos "mi_bd" y la colección "usuarios"
    collection = mongoc_client_get_collection(client, "localtest_db", "usuarios");

    // Operaciones CRUD
    insertar_usuario(collection);
    leer_usuarios(collection);
    actualizar_usuario(collection);
    leer_usuarios(collection);
    eliminar_usuario(collection);
    leer_usuarios(collection);

    // Liberar memoria y cerrar la conexión
    mongoc_collection_destroy(collection);
    mongoc_client_destroy(client);
    mongoc_cleanup();

    return 0;
}
