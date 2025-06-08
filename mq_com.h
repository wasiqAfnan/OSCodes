struct msg_buffer {
    long int ty;          // Message type (must be long)
    char text[1024];      // Message text content
};
// Declare a global message structure variable
struct msg_buffer data;
