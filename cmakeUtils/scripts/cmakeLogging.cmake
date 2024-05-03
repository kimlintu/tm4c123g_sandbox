function(log_message message)
    message("[CMAKE]: ${message}")
endfunction()

function(log_error_message message)
    message(SEND_ERROR "[CMAKE]: ${message}")
endfunction()

function(log_error_message_and_quit message)
    message(FATAL_ERROR "[CMAKE]: ${message}")
endfunction()