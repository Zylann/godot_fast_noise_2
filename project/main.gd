extends Node

@onready var _texture_rect : TextureRect = $TextureRect


func _ready():
	var noise := FastNoise2.new()
	var image := noise.get_image(512, 512, false, false, false)
	var texture := ImageTexture.create_from_image(image)
	_texture_rect.texture = texture
