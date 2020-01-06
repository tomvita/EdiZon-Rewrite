export VERSION_MAJOR 	:= 4
export VERSION_MINOR 	:= 0
export VERSION_MICRO 	:= 0
export SNAPSHOT		 	:= 1

export APP_TITLE		:=	EdiZon
export APP_AUTHOR		:=	WerWolv

.PHONY: clean all application sysmodule release

all: application sysmodule

--release:
	$(eval SNAPSHOT := 0)

release: --release clean sysmodule application

application:
	@printf "\x1b[32;01m ==== Building application ==== \x1b[0m\n"

	@$(MAKE) -C application --no-print-directory

	@printf "\x1b[32;01m ==== Compiled Successfully ==== \x1b[0m\n\n"

sysmodule:
	@printf "\x1b[32;01m ==== Building Sysmodule ==== \x1b[0m\n"

	@$(MAKE) -C sysmodule --no-print-directory

	@printf "\x1b[32;01m ==== Compiled Successfully ==== \x1b[0m\n\n"
	
	@rm -rf ./application/romfs/sysmodule
	@mkdir ./application/romfs/sysmodule
	@cp ./sysmodule/out/exefs.nsp ./application/romfs/sysmodule/exefs.nsp

install: application
	@$(MAKE) -C application install --no-print-directory

clean:
	@$(MAKE) -C application clean --no-print-directory
	@$(MAKE) -C sysmodule clean --no-print-directory
	