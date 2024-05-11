echo 'Atacar' >> __client_0_pipe__
echo 'Atacar' >> __client_1_pipe__
echo 'Atacar' >> __client_2_pipe__
echo 'Atacar' >> __client_2_pipe__
echo 'Atacar' >> __client_1_pipe__
echo 'Atacar' >> __client_0_pipe__


echo 'Leer 5' >> __client_0_pipe__
echo 'Leer 6' >> __client_1_pipe__
echo 'Leer 10' >> __client_2_pipe__

# Agrego el sleep para asegurarme que el server envia las
# acciones de revivir.
sleep 4

echo 'Salir' >> __client_0_pipe__
echo 'Salir' >> __client_1_pipe__
echo 'Salir' >> __client_2_pipe__
