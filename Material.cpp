#include "Material.hpp"

Material::Material() : Material(0.0f, 0.0f)
{
}

Material::Material(GLfloat sIntensity,
                   GLfloat shininess) : specularIntensity(sIntensity),
                                        shininess(shininess)
{
}

void Material::useMaterial(GLuint speculatIntensityLocation, GLuint ShininessLocation)
{
    glUniform1f(speculatIntensityLocation, specularIntensity);
    glUniform1f(ShininessLocation, shininess);

}

Material::~Material()
{
}