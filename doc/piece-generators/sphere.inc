sphere {
  0, 0.5
  pigment {
    gen_param[mod(pos.x + pos.y + pos.z, 2)]
  }
  translate 0.5
}
