#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int id_cliente;
    char nombre[50];
    char telefono[20];
}Cliente;

typedef struct{
    int codigo;
    char nombre[20];
    char categoria[20];
    float precio;
    int cantidad_comprada;
    float importe;
}Producto;

typedef struct{
    Cliente cliente;
    Producto productos[50];
    int total_productos;
}Compra;

int main() {
    int numero_clientes;
    printf("¿Cuántos clientes son en total? ");
    scanf("%d",&numero_clientes);
    Compra compras[numero_clientes];
     char categorias[5][20] = {
        "Abarrotes",
        "Electronica",
        "Papeleria",
        "Limpieza",
        "Bebidas"
    };
    
    char abarrotes[4][20] = {
        "Arroz", 
        "Aceite",
        "Sal",
        "Galletas"
    };
    float precios_abarrotes[4] = {30, 35, 18, 20};
    
    char electronica[4][20] = {
        "Laptop",
        "Teclado",
        "Mouse",
        "Cargador"
    };
    float precios_electronica[4] = {10000, 800, 300, 700};
    
    char papeleria[4][20] = {
        "Lápiz",
        "Tijeras",
        "Borrador",
        "Libreta"
    };
    float precios_papeleria[4] = {8, 15, 6, 50};
    
    char limpieza[4][20] = {
        "Detergente",
        "Pinol",
        "Clorox",
        "Lavatrastes"
    };
    float precios_limpieza[4] = {80, 25, 48, 70};

    char bebidas[4][20] = {
        "Refresco",
        "Jugos",
        "Energetizante",
        "Agua"
    };
    float precios_bebidas[4] = {25, 20, 18, 15};

    for(int i=0; i<numero_clientes; i++){
        printf("ID del cliente: ");
        scanf("%d",&compras[i].cliente.id_cliente);
        printf("Nombre del cliente: ");
        scanf("%s",compras[i].cliente.nombre);
        printf("Telefono del cliente: ");
        scanf("%s",compras[i].cliente.telefono);
        printf("Cuántos productos desea comprar? (Máximo 50) ");
        scanf("%d", &compras[i].total_productos);
        float subtotal_compra = 0;
        float IVA = 0;
        float total_pagar = 0;
        float descuento = 0;
        float total_con_descuento = 0;
        while(compras[i].total_productos <= 0 || compras[i].total_productos > 50){
            printf("Cantidad de productos no valida. Ingrese un valor entre 1 y 50: ");
            scanf("%d", &compras[i].total_productos);
        }
        for(int j=0; j<compras[i].total_productos; j++){
            int categoria=0;
            int producto_seleccionado=0;
            float precio=0;
            char *nombre_producto;
            char *categoria_elegida;
            int codigo_producto = 0;
            printf("\n==========CATEGORIAS=========\n");
            for(int k=0; k<5; k++){
                printf("%d.-%s\n", k+1, categorias[k]);
            };

            printf("\n==========SELECCIONE UNA CATEGORIA==========\n");
            scanf("%d",&categoria);
            printf("\n==========PRODUCTOS DISPONIBLES==========\n");
    
            switch(categoria){
                case 1:
                    categoria_elegida = categorias[0];
                    for(int m=0; m<4; m++){
                        printf("%d.-%s - $%.2f\n", m+1, abarrotes[m], precios_abarrotes[m]);
                    }
            
                    printf("\n==========¿Qué producto desea comprar?==========\n");
                    scanf("%d",&producto_seleccionado);
                    switch(producto_seleccionado){
                        case 1:
                            precio = 30;
                            nombre_producto = abarrotes[0];
                            codigo_producto = 1001;
                        break;
                        case 2:
                            precio = 35;
                            nombre_producto = abarrotes[1];
                            codigo_producto = 1002;
                        break;
                        case 3:
                            precio = 18;
                            nombre_producto = abarrotes[2];
                            codigo_producto = 1003;
                        break;
                        case 4:
                            precio = 20;
                            nombre_producto = abarrotes[3];
                            codigo_producto = 1004;
                        break;
                        default:
                            printf("Producto no válido\n");
                            continue;
                    }
                break;
                case 2:
                    categoria_elegida = categorias[1];
                    for(int m=0; m<4; m++){
                    printf("%d.-%s - $%.2f\n", m+1, electronica[m], precios_electronica[m]);
                    }
                    printf("\n==========¿Qué producto desea comprar?==========\n");
                    scanf("%d",&producto_seleccionado);
                    switch(producto_seleccionado){
                        case 1:
                            precio = 10000;
                            nombre_producto = electronica[0];
                            codigo_producto = 2001;
                        break;
                        case 2:
                            precio = 800;
                            nombre_producto = electronica[1];
                            codigo_producto = 2002;
                        break;
                        case 3:
                            precio = 300;
                            nombre_producto = electronica[2];
                            codigo_producto = 2003;
                        break;
                        case 4:
                            precio = 700;
                            nombre_producto = electronica[3];
                            codigo_producto = 2004;
                        break;
                        default:
                            printf("Producto no válido\n");
                            continue;
                }
                break;
                case 3:
                    categoria_elegida = categorias[2];
                    for(int m=0; m<4; m++){
                        printf("%d.-%s - $%.2f\n", m+1, papeleria[m], precios_papeleria[m]);
                    }
                    printf("\n==========¿Qué producto desea comprar?==========\n");
                    scanf("%d",&producto_seleccionado);
                    switch(producto_seleccionado){
                        case 1:
                            precio = 8;
                            nombre_producto = papeleria[0];
                            codigo_producto = 3001;
                        break;
                        case 2:
                            precio = 15;
                            nombre_producto = papeleria[1];
                            codigo_producto = 3002;
                        break;
                        case 3:
                            precio = 6;
                            nombre_producto = papeleria[2];
                            codigo_producto = 3003;
                        break;
                        case 4:
                            precio = 50;
                            nombre_producto = papeleria[3];
                            codigo_producto = 3004;
                        break;
                        default:
                            printf("Producto no válido\n");
                            continue;
                    }
                break;
                case 4:
                    categoria_elegida = categorias[3];
                    for(int m=0; m<4; m++){
                        printf("%d.-%s - $%.2f\n", m+1, limpieza[m], precios_limpieza[m]);
                    }
                    printf("\n==========¿Qué producto desea comprar?==========\n");
                    scanf("%d",&producto_seleccionado);
                    switch(producto_seleccionado){
                        case 1:
                            precio = 80;
                            nombre_producto = limpieza[0];
                            codigo_producto = 4001;
                        break;
                        case 2:
                            precio = 25;
                            nombre_producto = limpieza[1];
                            codigo_producto = 4002;
                        break;
                        case 3:
                            precio = 48;
                            nombre_producto = limpieza[2];
                            codigo_producto = 4003;
                        break;
                        case 4:
                            precio = 70;
                            nombre_producto = limpieza[3];
                            codigo_producto = 4004;
                        break;
                        default:
                            printf("Producto no válido\n");
                            continue;
                    }
                break;
                case 5:
                    categoria_elegida = categorias[4];
                    for(int m=0; m<4; m++){
                        printf("%d.-%s - $%.2f\n", m+1, bebidas[m], precios_bebidas[m]);
                    }
                    printf("\n==========¿Qué producto desea comprar?==========\n");
                    scanf("%d",&producto_seleccionado);
                    switch(producto_seleccionado){
                        case 1:
                            precio = 25;
                            nombre_producto = bebidas[0];
                            codigo_producto = 5001;
                        break;
                        case 2:
                            precio = 20;
                            nombre_producto = bebidas[1];
                            codigo_producto = 5002;
                        break;
                        case 3:
                            precio = 18;
                            nombre_producto = bebidas[2];
                            codigo_producto = 5003;
                        break;
                        case 4:
                            precio = 15;
                            nombre_producto = bebidas[3];
                            codigo_producto = 5004;
                        break;
                        default:
                            printf("Producto no válido\n");
                            continue;

                    }
                break;    
                default:
                    printf("Categoría no válida\n");
                    continue;
            
            }
            printf("\n==========¿Qué cantidad desea comprar?==========\n");
            scanf("%d",&compras[i].productos[j].cantidad_comprada);
            compras[i].productos[j].precio = precio;
            strcpy(compras[i].productos[j].nombre, nombre_producto);
            strcpy(compras[i].productos[j].categoria, categoria_elegida);
            compras[i].productos[j].codigo = codigo_producto;
            compras[i].productos[j].importe = compras[i].productos[j].precio * compras[i].productos[j].cantidad_comprada;
            subtotal_compra += compras[i].productos[j].importe;
            
        }   
        IVA = subtotal_compra * 0.16;
        total_pagar = subtotal_compra + IVA;

        total_con_descuento = total_pagar - descuento;
        printf("\n====================TICKET====================\n");
        printf("ID Cliente: %d\n", compras[i].cliente.id_cliente);
        printf("Nombre Cliente: %s\n", compras[i].cliente.nombre);
        printf("Telefono Cliente: %s\n", compras[i].cliente.telefono);
        printf("Productos Comprados:\n");
        for(int j=0; j<compras[i].total_productos; j++){
            printf("Código: %d\n", compras[i].productos[j].codigo);
            printf("Nombre: %s\n", compras[i].productos[j].nombre);
            printf("Categoría: %s\n", compras[i].productos[j].categoria);
            printf("Precio unitario: %.2f\n", compras[i].productos[j].precio);
            printf("Cantidad comprada: %d\n", compras[i].productos[j].cantidad_comprada);
            printf("Importe: %.2f\n", compras[i].productos[j].importe);
        }
        for(int j=0; j<compras[i].total_productos; j++){
            printf("\nSubtotal de %s: %.2f\n", compras[i].productos[j].nombre, compras[i].productos[j].importe);
        }
        printf("\nSubtotal de compra: %.2f\n", subtotal_compra);
        printf("IVA: %.2f\n", IVA);
        printf("\nTotal a pagar: %.2f\n", total_pagar);
        if(total_pagar > 5000 && total_pagar <= 10000){
            descuento = total_pagar * 0.1;
            total_con_descuento = total_pagar - descuento;
            printf("\nDescuento aplicado: %.2f\nTotal con descuento: %.2f\n", descuento, total_con_descuento);
        }
        else if(total_pagar > 10000){
            descuento = total_pagar * 0.15;
            total_con_descuento = total_pagar - descuento;
            printf("\nDescuento aplicado: %.2f\nTotal con descuento: %.2f\n", descuento, total_con_descuento);
        }
        printf("\n================================================================\n");
    }   
    return 0;
}