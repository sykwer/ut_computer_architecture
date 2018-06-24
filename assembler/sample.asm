    addi r1, r0, 1
    addi r2, r0, 1
    addi r3, r0, 1
    addi r4, r0, 1
    addi r5, r0, 1
    addi r6, r0, 1
    addi r9, r0, 9
    addi r12, r0, 12
    addi r14, r0, 14
    addi r15, r0, 15
    addi r19, r0, 19
label5:  addi r30, r0, 30
label1:  sub r7, r4, r6
    lui r8, 12
    and r10, r8, r9
    andi r11, r10, 15
    or r13, r11, r12
    xor r16, r14, r15
    xori r17 r16, 31
    ori r18, r15, 7
    nor r20, r18, r19
    beq r7, r8, label1
    sll r21, r20, 5
    sra r22, r21, 3
    srl r23, r22, 2
    bne r9, r10, label2
label2: sw r2, 0(r1)
    sb r6, -10(r5)
    sh r4, 8(r3)
label4: lw r25, 0(r1)
    lh r27, -10(r5)
    lb r29, 8(r3)
    blt r11, r12, label3
    ble r13, r14, label4
    j label5
    jal label5
label3:  jr r31
