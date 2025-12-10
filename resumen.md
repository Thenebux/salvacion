# ✅ FICHA RESUMEN – MÉTODOS Y FUNCIONES ÚTILES EN C++

---

## 🔵 1. FUNCIONES DE CADENAS (`string`)
**Fuente:** Manual de cadenas

| Método | Uso |
|-------|-----|
| `s.length()` | Cantidad de caracteres |
| `s.size()` | Igual que length |
| `s.append(txt)` | Agregar texto |
| `s + txt` | Concatenar |
| `s.substr(pos, len)` | Subcadena |
| `s.find(txt)` | Buscar posición |
| `s.replace(pos, len, txt)` | Reemplazar parte |
| `s.erase(pos, len)` | Eliminar parte |
| `s.insert(pos, txt)` | Insertar |
| `s.clear()` | Vaciar cadena |
| `s.empty()` | ¿Vacía? |
| `s.at(i)` | Carácter seguro |
| `s.compare(otra)` | 0 → iguales |

---

## 🔵 2. FUNCIONES DE CARACTER (`<cctype>`)
| Función | Significado |
|--------|-------------|
| `isalpha(c)` | ¿Letra? |
| `isdigit(c)` | ¿Número? |
| `isalnum(c)` | ¿Letra o número? |
| `islower(c)` | ¿Minúscula? |
| `isupper(c)` | ¿Mayúscula? |
| `isspace(c)` | ¿Espacio/tab? |
| `ispunct(c)` | ¿Signo? |
| `tolower(c)` | → minúscula |
| `toupper(c)` | → mayúscula |

---

## 🔵 3. FUNCIONES DE CADENAS CON `char[]` (`<cstring>`)
| Función | Uso |
|---------|-----|
| `strlen(cad)` | Longitud |
| `strcpy(dest, src)` | Copiar |
| `strcat(dest, src)` | Concatenar |
| `strcmp(a,b)` | 0 → iguales |
| `strchr(cad, c)` | Buscar carácter |
| `strstr(cad, sub)` | Subcadena |

---

## 🔵 4. ARRAYS Y PUNTEROS

### Acceso
```cpp
*(ptr + i);   // arr[i]
