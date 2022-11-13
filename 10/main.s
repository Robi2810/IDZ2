    .intel_syntax noprefix

    .bss
    .lcomm _out_fname, 128
    .equ _string_limit, 4096
    .equ _string_big_limit, 134217728
    .lcomm string_buf, _string_limit
    .lcomm substring_buf, _string_limit
    ReadStartTime: .space 16
    ReadEndTime: .space 16
    ReadDeltaTime: .space 16
    CalcStartTime: .space 16
    CalcEndTime: .space 16
    CalcDeltaTime: .space 16
    WriteStartTime: .space 16
    WriteEndTime: .space 16
    WriteDeltaTime: .space 16

    .text
    .global _start
msg_inv_args:
    .string "Invalid args count. See README file for corect usage.\n"
msg_inv_flag:
    .string "Invalid flag. See README file for corect usage.\n"
msg_inv_chars:
    .string "Invalid chars in string. Must be in range [0-127].\n"
msg_enter_str:
    .string "Enter the string: "
msg_enter_substr:
    .string "Enter the substring: "
msg_gen_str:
    .string "Generated string: "
msg_result:
    .string "Result: "
msg_len_big:
    .string "Length is greater than limit!\n"
msg_err:
    .string "Error while opening a file: "
msg_new_line:
    .string "\n"
msg_time:
    .string "Elapsed time:  \n"
msg_time_read:
    .string "Read:          "
msg_time_calc:
    .string "Calculations:  "
msg_time_write:
    .string "Write:         "
flag_file:
    .string "-f"
flag_random:
    .string "-r"
flag_console:
    .string "-c"

_start:
    mov r12, [rsp]
    cmp r12, 2                          # check number of args
    jl inv_args_count                   # if < 2 display error message                                 
    mov rcx, 16[rsp]
    mov rax, rcx
    mov rbx, offset flag_console
    call compare_strings
    cmp rax, 1
    je .console_input
    mov rax, rcx
    mov rbx, offset flag_random
    call compare_strings
    cmp rax, 1
    je .random_input
    mov rax, rcx
    mov rbx, offset flag_file
    call compare_strings
    cmp rax, 1
    je .file_input
    mov rax, offset msg_inv_flag
    call print_string
    jmp exit

.console_input:
    mov rax, offset msg_enter_str
    call print_string
    call input_string                           # get string
    mov rax, offset _str_buffer
    mov rbx, offset string_buf
    call copy_string
    jmp .strbuf_to_array

.random_input:
    cmp r12, 3
    jne inv_args_count
    mov rax, 24[rsp]                            # get length of string
    call string_to_num
    cmp rax, _string_limit
    jg len_too_big
    mov rbx, offset string_buf
    call get_random_string                      # generate random string given length
    
    mov rax, offset msg_gen_str
    call print_string
    mov rax, offset string_buf
    call print_string
    call print_line

    jmp .strbuf_to_array

.strbuf_to_array:
    mov rax, offset string_buf
    call length_string
    mov r12, rax
    call create_array                   # create string
    mov r14, rdi

    mov rax, offset string_buf
    mov rbx, r14
    call copy_string

    mov r12, 0
    jmp .do_task

.file_input:
    lea rax, ReadStartTime[rip]
    call time_now
    cmp r12, 4
    jne inv_args_count
    mov rax, _string_big_limit
    call create_array                   # create string
    mov r14, rdi
   

    mov rax, 24[rsp]                    # store in rax filename input
    mov rdx, rax
    mov rbx, 0                          # 0 - read
    call file_open

    cmp rax, -1                         # if error
    jl .file_open_error

    push rax
    mov rbx, r14
    mov rcx, _string_big_limit
    call file_read_string_line
    pop rax
    call file_close
    
    mov rax, 32[rsp]
    mov rbx, offset _out_fname
    call copy_string
    lea rax, ReadEndTime[rip]
    call time_now
    mov r12, 1

    jmp .do_task

    
.do_task:
    # check for invalid ascii codes 
    mov rdx, r12
    lea rax, CalcStartTime[rip]
    call time_now
    mov rax, r14
    mov rbx, 128
    call find_chars_by_code
    cmp rax, 0
    jge .inv_chars
    
    mov rax, r14
    call length_string
    mov rbx, rax
    mov rax, r14
    call change

    lea rax, CalcEndTime[rip]
    call time_now
    cmp rdx, 0
    jg .file_output
    jmp .console_output

.console_output:
    mov rax, offset msg_result
    call print_string
    mov rax, r14
    call print_string
    call print_line

    mov rax, _string_big_limit
    mov rdi, r14
    call free_array
    mov rax, rbx
    jmp exit

.file_output:
    lea rax, WriteStartTime[rip]
    call time_now
    mov rax, offset _out_fname
    call file_create
    mov rbx, 289                        # write + append
    mov r13, rax
    call file_open
    mov rbx, r14
    mov rax, r14
    call length_string
    mov rcx, rax
    mov rax, r13
    call file_write_line
    mov rax, r13
    call file_close
    lea rax, WriteEndTime[rip]
    call time_now

.print_time:
    # print time results for file IO
    # for read
    mov rax, ReadStartTime[rip]
    mov rbx, ReadStartTime[rip + 8]
    mov rcx, ReadEndTime[rip]
    mov rdx, ReadEndTime[rip + 8]
    lea r8, ReadDeltaTime[rip]
    lea r9, ReadDeltaTime[rip + 8]
    call get_delta

    # for calc
    mov rax, CalcStartTime[rip]
    mov rbx, CalcStartTime[rip + 8]
    mov rcx, CalcEndTime[rip]
    mov rdx, CalcEndTime[rip + 8]
    lea r8, CalcDeltaTime[rip]
    lea r9, CalcDeltaTime[rip + 8]
    call get_delta
    
    # for write
    mov rax, WriteStartTime[rip]
    mov rbx, WriteStartTime[rip + 8]
    mov rcx, WriteEndTime[rip]
    mov rdx, WriteEndTime[rip + 8]
    lea r8, WriteDeltaTime[rip]
    lea r9, WriteDeltaTime[rip + 8]
    call get_delta

    
    mov rax, offset msg_time
    call print_string

    mov rax, offset msg_time_read
    call print_string
    mov rax, ReadDeltaTime[rip]
    call print_number
    mov rax, '.'
    call print_char
    mov rax, ReadDeltaTime[rip+8]
    call print_number
    call print_line
    
    mov rax, offset msg_time_calc
    call print_string
    mov rax, CalcDeltaTime[rip]
    call print_number
    mov rax, '.'
    call print_char
    mov rax, CalcDeltaTime[rip+8]
    call print_number
    call print_line

    mov rax, offset msg_time_write
    call print_string
    mov rax, WriteDeltaTime[rip]
    call print_number
    mov rax, '.'
    call print_char
    mov rax, WriteDeltaTime[rip+8]
    call print_number
    call print_line    
    jmp exit

.file_open_error:
    mov rax, offset msg_err
    call print_string
    mov rax, rdx
    call print_string
    call print_line
    jmp exit

len_too_big:
    mov rax, offset msg_len_big
    call print_string
    jmp exit
    
.inv_chars:
    mov rax, offset msg_inv_chars
    call print_string
    jmp exit

inv_args_count:
    mov rax, offset msg_inv_args
    call print_string
    jmp exit         

exit:
	mov rax, 60
	mov rdi, 0
	syscall


change:
    push rcx
    push rdx
    mov rcx, 0
.f1: 
    cmp rcx, rbx
    jge .change_exit
    mov dl, byte ptr[rax+rcx]
    inc rcx
    cmp dl, 65
    jl .f1
    cmp dl, 90
    jg .f2
    add dl, 32
    mov byte ptr[rax+rcx-1], dl
    jmp .f1
.f2:
    cmp dl, 97
    jl .f1
    cmp dl, 122
    jg .f1
    sub dl, 32
    mov byte ptr[rax+rcx-1], dl
    jmp .f1
.change_exit:
    pop rdx
    pop rcx
    ret