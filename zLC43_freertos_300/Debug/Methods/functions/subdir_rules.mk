################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Methods/functions/%.obj: ../Methods/functions/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7R5 --code_state=32 --float_support=VFPv3D16 --include_path="C:/Users/Eduardo/workspace_v12/zLC43_freertos_300" --include_path="C:/Users/Eduardo/workspace_v12/zLC43_freertos_300/include" --include_path="C:/Users/Eduardo/workspace_v12/zLC43_freertos_300/Methods/headers" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="Methods/functions/$(basename $(<F)).d_raw" --obj_directory="Methods/functions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


