//fragment shader
#version 400 core

layout(location = 0) out vec4 out_color;

in vec4 nativeVaocolor;

uniform vec4 gridcolor;//this is for the color of the uniform grid

uniform sampler2D tex;  // color map
uniform sampler2D tex1; // normal map

in vec2 uvVert;


uniform struct Light {
   vec3 position;
   vec3 intensities; // the color of the light
   float ambientCoefficient;
} light;

uniform mat4 modelmatrixcube;
in vec3 fragVert;
in vec2 fragTexCoord;
in vec3 fragNormal;




// http://www.thetenthplanet.de/archives/1180
mat3 cotangent_frame(vec3 N, vec3 p, vec2 uv)
{
    // get edge vectors of the pixel triangle
    vec3 dp1 = dFdx( p );
    vec3 dp2 = dFdy( p );
    vec2 duv1 = dFdx( uv );
    vec2 duv2 = dFdy( uv );

    // solve the linear system
    vec3 dp2perp = cross( dp2, N );
    vec3 dp1perp = cross( N, dp1 );
    vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
    vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;

    // construct a scale-invariant frame
    float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );
    return mat3( T * invmax, B * invmax, N );
}

vec3 perturb_normal( vec3 N, vec3 V, vec2 texcoord )
{
    // assume N, the interpolated vertex normal and
    // V, the view vector (vertex to eye)
   vec3 map = texture2D(tex1, texcoord ).xyz;
   map = map * 255./127. - 128./127.;
    mat3 TBN = cotangent_frame(N, -V, texcoord);
    return normalize(TBN * map);
}


void main()
{

//Lighting calculations for the 2nd textured cube

   //calculate normal in world coordinates
    mat3 normalMatrix = transpose(inverse(mat3(modelmatrixcube)));
    vec3 normal = normalize(normalMatrix * fragNormal);


    //Used fro normal mapping - with no precomputed bitangets & binormals
    vec3 PN = perturb_normal(normal, fragVert, fragTexCoord.xy);

    //calculate the location of this fragment (pixel) in world coordinates
    vec3 surfacePos = vec3(modelmatrixcube * vec4(fragVert, 1));

    //calculate the vector from this pixels surface to the light source
    vec3 surfaceToLight = normalize(light.position - surfacePos);

    //calculate the cosine of the angle of incidence
    float diffuseCoefficient = max(0.0, dot(PN, surfaceToLight));

    //calculate final color of the pixel, based on:
    // 1. The angle of incidence: diffuseCoefficient
    // 2. The color/intensities of the light: light.intensities
    // 3. The texture and texture coord: texture(tex, fragTexCoord)
    vec4 surfaceColor = texture(tex, fragTexCoord);


    //ambient
    vec3 ambient = light.ambientCoefficient * surfaceColor.rgb * light.intensities;

    vec3 diffuse = vec3(diffuseCoefficient * light.intensities * surfaceColor.rgb);




  if(gridcolor!=0)// this is for the color of the uniform grid
     out_color = gridcolor;
   else if (fragTexCoord!=0)
     out_color = vec4(diffuse*ambient, surfaceColor.a);// this is for the shading of the 2nd small textured cube
   else
     out_color = nativeVaocolor;// this is for the shading of the 1st big cube

}





///////////////////////////////////////////////////////////////////////////////////////////

//// array of light vectors passed from vert shader
//in vec3 lightVec;
//// array of half vects from vert shader
//in vec3 halfVec;

//// spec power passed from client program (or could use alpha of spec map if present)
//uniform float specPower;


//in vec3 lightDir;
//// out the blinn half vector
//in vec3 halfVector;


///// @brief our output fragment colour
//vec4 fragColour;

//void main ()
//{
//    fragColour=vec4(0);
//    // lookup normal from normal map, move from [0,1] to  [-1, 1] range, normalize
//    vec3 normal=normalize( texture2D(tex1, fragTexCoord.st).xyz * 2.0 - 1.0);
//    // we need to flip the z as this is done in zBrush
//    normal.z = -normal.z;
//    // default material values to be accumulated
//    float lamberFactor=1;
//    vec4 diffuseMaterial = texture2D(tex, fragTexCoord.st);
//    // compute specular lighting
//    //vec4 specularMaterial=texture2D(spec, fragTexCoord.st)  ;

//    float shininess ;

//    lamberFactor= max (dot (lightVec, normal), 0.0) ;
//    // so light is hitting use here calculate and accumulate values
////    if (lamberFactor > 0.0)
//    {
//            // get the phong / blinn values
//            //shininess = pow (max (dot ( halfVec[i],normal), 0.0), specPower);
//            fragColour = diffuseMaterial * light.ambientCoefficient * lamberFactor;
//            //fragColour +=	specularMaterial * light[i].specular * shininess;
//    }




// if(gridcolor!=0)// this is for the color of the uniform grid
//    out_color = gridcolor;
//  else if (fragTexCoord!=0)
//    out_color = fragColour;
//  else
//    out_color = nativeVaocolor;


//}
