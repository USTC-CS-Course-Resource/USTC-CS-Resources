
	.text
	.globl main
main:
	# Generate the random numbers
	la	$a0, array
	lw	$a1, N
	jal	array_generate
	# Start time
	li	$v0, 30
	syscall
	move	$s4, $a0
	move	$s5, $a1
	# Sort
	la	$a0, array
	lw	$a1, N
	jal	bubble_sort
	# End time
	li	$v0, 30
	syscall
	move	$s6, $a0
	move	$s7, $a1
	sub	$s6, $s6, $s4
	sub	$s7, $s7, $s5
	# Print time consumed(only considering about the lower bits of time)
	li	$v0, 1
	move	$a0, $s6
	syscall
	# Halt
	li	$v0, 10
	syscall
	
	
# Bubble Sort from small to large	
bubble_sort:
	# Register assignments
	# $s1 = &array[i], i is from N to 1
	# $s2 = &array[j], j is from 1 to i-1
	# $s3 = &array[0]
	# $t0, temp for swap
	# $t1 = array[j-1]
	# $t2 = array[j]
	
	# Save registers
	addi $sp, $sp, -4		# Adjust stack pointer
	sw $s1, 0($sp)			# Save $s1
	addi $sp, $sp, -4		# Adjust stack pointer
	sw $s2, 0($sp)			# Save $s2
	addi $sp, $sp, -4		# Adjust stack pointer
	sw $s3, 0($sp)			# Save $s3
	
	# Start the sort loops
	move	$s1, $a1		# get the size of the array
	sll	$s1, $s1, 2
	move	$s3, $a0
	add	$s1, $s3, $s1		# let $s3 store the last element's address in the array
	add	$s3, $s3, 4
loop1:
	ble	$s1, $s3, exit1
	add	$s2, $s3, 0
loop2:
	beq	$s1, $s2, exit2
	lw	$t1, -4($s2)
	lw	$t2, 0($s2)
	ble	$t1, $t2, noswap 
	sw	$t1, 0($s2)		# swap
	sw	$t2, -4($s2)		# swap
noswap:
	add	$s2, $s2, 4
	j	loop2
exit2:
	add	$s1, $s1, -4
	j	loop1
exit1:
	# Sorting finished, restore the registers
	lw $s3, 0($sp)			# Restore $s3
	addi $sp, $sp, 4		# Adjust stack pointer
	lw $s2, 0($sp)			# Restore $s2
	addi $sp, $sp, 4		# Adjust stack pointer
	lw $s1, 0($sp)			# Restore $s1
	addi $sp, $sp, 4		# Adjust stack pointer
	# return
	jr	$ra

array_generate:
	move	$s1, $a0
	move	$s2, $a1
loop_gen:
	beq	$s2, 0, exit
	li	$v0, 42
	li	$a1, 10000
	syscall
	sw	$a0, 0($s1)
	add	$s2, $s2, -1
	add	$s1, $s1, 4
	j	loop_gen
exit:
	jr	$ra
	.data
N:	.word	40			# amount of the numbers
array:	.space	4000
	