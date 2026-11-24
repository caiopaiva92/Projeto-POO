# Makefile fino: so chama o CMake. Quem compila de verdade e o CMakeLists.txt.
BUILD := build
EXE   := $(BUILD)/app

.PHONY: all roda verifica limpa

# make: configura e compila
all:
	cmake -S . -B $(BUILD) -G "Unix Makefiles"
	cmake --build $(BUILD)

# make roda: compila e executa a demonstracao
roda: all
	./$(EXE)

# make verifica: o portao. Compila (biblioteca com -Werror), roda e confere
# que a ultima linha da saida e vivos=0
verifica: all
	./$(EXE) > $(BUILD)/saida.txt
	@ultima=$$(tail -n 1 $(BUILD)/saida.txt | tr -d '\r'); \
	if [ "$$ultima" = "vivos=0" ]; then \
		echo "verifica: OK (ultima linha: $$ultima)"; \
	else \
		echo "verifica: FALHOU (ultima linha: $$ultima)"; exit 1; \
	fi

# make limpa: apaga a pasta de compilacao
limpa:
	rm -rf $(BUILD)