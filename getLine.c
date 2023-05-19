#include "shell.h"

/**
 * bufferInput - buffers the input
 * @info: info struct
 * @buf: buffer
 * @len: length
 *
 * Return: bytesRead
 */
ssize_t bufferInput(info_t *info, char **buffer, size_t *length)
{
    ssize_t bytesRead = 0;
    size_t lengthRead = 0;

    if (!*length)
    {
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, handleSigint);
#if USE_GETLINE
        bytesRead = getline(buffer, &lengthRead, stdin);
#else
        bytesRead = getLine(info, buffer, &lengthRead);
#endif
        if (bytesRead > 0)
        {
            if ((*buffer)[bytesRead - 1] == '\n')
            {
                (*buffer)[bytesRead - 1] = '\0';
                bytesRead--;
            }
            info->lineCountFlag = 1;
            removeComments(*buffer);
            buildHistoryList(info, *buffer, info->historyCount++);
            {
                *length = bytesRead;
                info->commandBuffer = buffer;
            }
        }
    }
    return (bytesRead);
}

/**
 * getInput - gets input from the user
 * @info: info struct
 *
 * Return: bytesRead
 */
ssize_t getInput(info_t *info)
{
    static char *buffer;
    static size_t i, j, length;
    ssize_t bytesRead = 0;
    char **bufferPointer = &(info->argument), *p;

    _putchar(BUF_FLUSH);
    bytesRead = bufferInput(info, &buffer, &length);
    if (bytesRead == -1)
        return (-1);
    if (length)
    {
        j = i;
        p = buffer + i;

        checkChain(info, buffer, &j, i, length);
        while (j < length)
        {
            if (isChain(info, buffer, &j))
                break;
            j++;
        }

        i = j + 1;
        if (i >= length)
        {
            i = length = 0;
            info->cmd_buf_type = CMD_NORM;
        }

        *bufferPointer = p;
        return (_strlen(p));
    }

    *bufferPointer = buffer;
    return (bytesRead);
}

/**
 * readBuffer - reads yhe buffer
 * @info: info struct
 * @buf: buffer
 * @i: size
 *
 * Return: bytesRead
 */
ssize_t readBuffer(info_t *info, char *buffer, size_t *i)
{
    ssize_t bytesRead = 0;

    if (*i)
        return (0);
    bytesRead = read(info->readfd, buffer, READ_BUF_SIZE);
    if (bytesRead >= 0)
        *i = bytesRead;
    return (bytesRead);
}

/**
 * getLine - reads a line from a file descriptor
 * @info: the parameter & return info struct
 * @ptr: pointer to a buffer to store the line
 * @length: pointer to the length of the buffer
 *
 * Return: size
 */
int getLine(info_t *info, char **ptr, size_t *length)
{
    static char buffer[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t bytesRead = 0, size = 0;
    char *p = NULL, *newPtr = NULL, *c;

    p = *ptr;
    if (p && length)
        size = *length;
    if (i == len)
        i = len = 0;

    bytesRead = readBuffer(info, buffer, &len);
    if (bytesRead == -1 || (bytesRead == 0 && len == 0))
        return (-1);

    c = _strchr(buffer + i, '\n');
    k = c ? 1 + (unsigned int)(c - buffer) : len;
    newPtr = _realloc(p, size, size ? size + k : k + 1);
    if (!newPtr)
        return (p ? free(p), -1 : -1);

    if (size)
        _strncat(newPtr, buffer + i, k - i);
    else
        _strncpy(newPtr, buffer + i, k - i + 1);

    size += k - i;
    i = k;
    p = newPtr;

    if (length)
        *length = size;
    *ptr = p;
    return (size);
}

/**
 * handleSigint - handles the SIGINT signal
 * @sig_num: the signal number
 *
 * Return: void
 */
void handleSigint(__attribute__((unused))int signalNumber)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}
